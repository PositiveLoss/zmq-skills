<?php
declare(strict_types=1);

// CLI fixture for the C ROUTER service. Requires PHP with a verified ext-zmq.
// This code is an adaptation fixture; inspect the exact extension ABI/API.
function request(string $endpoint, string $payload): string
{
    if (strlen($payload) > 65536) {
        throw new InvalidArgumentException('Payload exceeds 65536 bytes');
    }
    $context = null;
    $socket = null;
    $poll = null;
    $deadline = hrtime(true) + 1000000000;
    $id = bin2hex(random_bytes(16));
    try {
        $context = new ZMQContext(1, false);
        $socket = new ZMQSocket($context, ZMQ::SOCKET_DEALER);
        foreach (['LINGER' => 0, 'SNDHWM' => 128, 'RCVHWM' => 128,
                  'IMMEDIATE' => 1, 'MAXMSGSIZE' => 65536] as $name => $value) {
            $constant = 'ZMQ::SOCKOPT_' . $name;
            if (!defined($constant)) {
                throw new RuntimeException('Required extension option unavailable: ' . $name);
            }
            $socket->setSockOpt(constant($constant), $value);
        }
        $socket->connect($endpoint);
        $poll = new ZMQPoll();
        $poll->add($socket, ZMQ::POLL_OUT);
        $readable = [];
        $writable = [];
        $remaining = (int) ceil(($deadline - hrtime(true)) / 1000000);
        if ($remaining <= 0 || $poll->poll($readable, $writable, $remaining) === 0 || !$writable) {
            throw new RuntimeException('Send deadline exceeded');
        }
        if ($socket->sendMulti(['v1', $id, $payload], ZMQ::MODE_DONTWAIT) === false) {
            throw new RuntimeException('Send would block; no multipart retry in this fixture');
        }
        $poll->clear();
        $poll->add($socket, ZMQ::POLL_IN);
        while (true) {
            $remaining = (int) ceil(($deadline - hrtime(true)) / 1000000);
            if ($remaining <= 0) {
                throw new RuntimeException('Reply deadline exceeded; remote outcome unknown');
            }
            $readable = [];
            $writable = [];
            if ($poll->poll($readable, $writable, $remaining) === 0 || !$readable) {
                continue;
            }
            try {
                $reply = $socket->recvMulti(ZMQ::MODE_DONTWAIT);
            } catch (ZMQSocketException $error) {
                if ($error->getCode() === ZMQ::ERR_EAGAIN) {
                    continue;
                }
                throw $error;
            }
            if ($reply === false) {
                continue;
            }
            if (count($reply) !== 3 || $reply[0] !== 'v1' || $reply[1] !== $id ||
                !is_string($reply[2]) || strlen($reply[2]) > 65536) {
                throw new RuntimeException('Invalid reply framing or correlation');
            }
            return $reply[2];
        }
    } finally {
        // No invented native close()/term() methods. Nonpersistent references only.
        if ($poll !== null) {
            $poll->clear();
        }
        $poll = null;
        $socket = null;
        $context = null;
    }
}

try {
    if (PHP_SAPI !== 'cli' || PHP_INT_SIZE < 8 || !extension_loaded('zmq')) {
        throw new RuntimeException('Requires 64-bit PHP CLI with ext-zmq and hrtime support');
    }
    if ($argc < 2 || $argc > 3 || preg_match('/^tcp:\/\/127\.0\.0\.1:[0-9]+$/D', $argv[1]) !== 1) {
        throw new InvalidArgumentException('Usage: php request.php tcp://127.0.0.1:PORT [text]');
    }
    $payload = $argv[2] ?? "A\0B\xff";
    $reply = request($argv[1], $payload);
    if ($reply !== $payload) {
        throw new RuntimeException('Binary echo mismatch');
    }
    fwrite(STDOUT, bin2hex($reply) . PHP_EOL);
} catch (Throwable $error) {
    fwrite(STDERR, $error->getMessage() . PHP_EOL);
    exit(1);
}
