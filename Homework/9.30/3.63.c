long switch_prob(long x, long n) {
    long result = x;
    switch (n) {
    case 60:
    case 62:
        result = 8 * x;
        break;
    case 63:
        result = x >> 3;
        break;
    case 64:
        x = (x << 4) - x;
        __attribute__((fallthrough));
    case 65:
        x *= x;
        __attribute__((fallthrough));
    default:
        result = x + 75;
    }
    return result;
}
