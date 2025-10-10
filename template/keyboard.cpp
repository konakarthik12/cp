#pragma once

#ifdef LOCAL
// macOS / POSIX (works even if stdin is redirected)
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cerrno>
#include <cstring>

class TtyGuard {
 public:
  explicit TtyGuard(int fd) : fd_(fd), ok_(false) {
    if (tcgetattr(fd_, &orig_) == 0) {
      raw_ = orig_;

      // disable canonical mode (line buffering) and echo,
      // but keep ISIG so Ctrl-C / Ctrl-Z still send signals
      raw_.c_lflag &= ~(ICANON | ECHO);

      // control read behavior: return after 1 char
      raw_.c_cc[VMIN] = 1;
      raw_.c_cc[VTIME] = 0;

      if (tcsetattr(fd_, TCSANOW, &raw_) == 0) ok_ = true;
    }
  }
  ~TtyGuard() {
    if (ok_) tcsetattr(fd_, TCSANOW, &orig_);
  }
  bool good() const {
    return ok_;
  }

 private:
  int fd_;
  termios orig_{};
  termios raw_{};
  bool ok_;
};

void wait_for_spacebar() {
  // Open controlling terminal explicitly, independent of stdin/stdout redirection
  int fd = open("/dev/tty", O_RDONLY);
  if (fd == -1) {
    std::cerr << "Failed to open /dev/tty: " << std::strerror(errno) << "\n";
    exit(1);
  }

  TtyGuard guard(fd);
  if (!guard.good()) {
    std::cerr << "Failed to configure terminal for raw input.\n";
    exit(1);
  }

  // std::cout << "Press spacebar to continue...\n" << std::flush;

  char ch;
  while (true) {

    ssize_t n = ::read(fd, &ch, 1);
    if (n == 1) {
      if (ch == ' ') break;
      // ignore other keys
    } else if (n == -1 && errno != EINTR) {
      std::cerr << "Read error: " << std::strerror(errno) << "\n";
      exit(1);
    }
  }

  close(fd);
}

#endif
