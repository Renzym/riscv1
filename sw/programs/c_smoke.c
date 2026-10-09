/* Exercises Data.hex initialization, BSS, stack, calls and Harvard rodata. */
static volatile unsigned int initialized = 0x12345670u;
static volatile unsigned int zeroed;
static const unsigned int constants[] = {8u, 3u};

__attribute__((noinline)) static unsigned int add_on_stack(unsigned int value)
{
    volatile unsigned int local = value;
    // Volatile BSS supplies a runtime index, preventing constant folding of
    // the read-only table and exercising loads from Harvard data RAM.
    return local + constants[zeroed];
}

int main(void)
{
    volatile unsigned int *signature = (volatile unsigned int *)0x40u;
    *signature = zeroed == 0 && constants[zeroed + 1] == 3 ? add_on_stack(initialized) : 0;
    return 0;
}
