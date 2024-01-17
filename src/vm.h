int vm(char* src) {
  unsigned int ip = 0;
  char memory[MEMSIZE];
  regsize regs[16];
  regsize exitReg;
  flagsize flags;
  short res;
  bufsize addr_buf;
  bufsize size_buf;
  while (true) {
    if (src[ip] == 0x00) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] += regs[(int)src[ip+2]];
      else
        ip += regs[(int)src[ip+2]];
      ip += 3;
    }
    else if (src[ip] == 0x01) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] += src[ip+2];
      else
        ip += src[ip+2];
      ip += 3;
    }
    else if (src[ip] == 0x02) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] = src[ip+2];
      else
        ip = src[ip+2];
      ip += 3;
    }
    else if (src[ip] == 0x03) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] -= regs[(int)src[ip+2]];
      else
        ip -= regs[(int)src[ip+2]];
      ip += 3;
    }
    else if (src[ip] == 0x04) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] -= src[ip+2];
      else
        ip -= src[ip+2];
      ip += 3;
    }
    else if (src[ip] == 0x05) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] *= regs[(int)src[ip+2]];
      else
        ip *= regs[(int)src[ip+2]];
      ip += 3;
    }
    else if (src[ip] == 0x06) {
      if (src[ip+1] != 0x14)
        regs[(int)src[ip+1]] *= src[ip+2];
      else
        ip *= src[ip+2];
      ip += 3;
    }
    else if (src[ip] == 0x0A) {
      ip++;
      size_buf = (src[ip]);
      addr_buf = (src[ip+1] << 24) + (src[ip+2] << 16) + (src[ip+3] << 8) + (src[ip+4]);
      ip += 5;
      regs[(int)size_buf] = memory[addr_buf];
    }
    else if (src[ip] == 0x0E) {
      res = (regs[(int)src[ip+1]] - regs[(int)src[ip+2]]);
      printf("INS-0Eh-L: Result: %xh\n", res);
      if (res < 0) flags = (flags | 0x0001);
      else flags = (flags & 0xFFFE);
      if (res == 0) flags = (flags | 0x0002);
      else flags = (flags & 0xFFFD);
      printf("INS-0Eh-L: Flags: %xh\n", flags);
      ip += 3;
    }
    else if (src[ip] == 0x10) {
      ip = (src[ip+1] << 24) + (src[ip+2] << 16) + (src[ip+3] << 8) + (src[ip+4]);
    }
    else if (src[ip] == 0x11) {
      printf("INS-11h-L: Flags: %xh\n", flags);
      if (flags & 0x0002)
        ip = (src[ip+1] << 24) + (src[ip+2] << 16) + (src[ip+3] << 8) + (src[ip+4]);
      else
        ip += 5;
    }
    else if (src[ip] == 0x12) {
      printf("INS-12h-L: Flags: %xh\n", flags);
      if (flags & 0x0001)
        ip = (src[ip+1] << 24) + (src[ip+2] << 16) + (src[ip+3] << 8) + (src[ip+4]);
      else
        ip += 5;
    }
    else if (src[ip] == 0x20) {
      addr_buf = (src[ip+1] << 24) + (src[ip+2] << 16) + (src[ip+3] << 8) + (src[ip+4]);
      ip += 5;
      size_buf = (src[ip]);
      ip++;
      for (short i = 0; i < size_buf; i++) {
        memory[i+addr_buf] = src[ip+i];
      }
      for (short i = 0; i < 10; i++) {
        printf("INS-20h-L: Memory Address %xh: %xh\n", i, memory[i]);
      }
      ip += 2;
    }
    else if (src[ip] == 0x2A) {
      ip++;
      if (regs[7] == 0x01) {
        exitReg = regs[8];
        break;
      }
      else if (regs[7] == 0x02) {
        if (regs[8] == 0x01) {
          fprintf(stdout, "%c", regs[9]);
        }
        else if (regs[8] == 0x02) {
          fprintf(stderr, "%c", regs[9]);
        }
        else {
          printf("Error! Invalid stdfile: %xh\n", regs[8]);
          exit(1);
        }
      }
      else {
        printf("Error! Illegal kcall: %xh\n", regs[7]);
        exit(1);
      }
    }
    else if (src[ip] == 0x40) {
      ip++;
    }
    else {
      printf("Error! Illegal instruction %xh\n", src[ip]);
      exit(1);
    }
  }

  return exitReg;
}

