/* Minimal freestanding C example for generating Program.hex.
 * This is not the default scoreboard regression; use PROG=c_smoke explicitly.
 */
void _start(void)
{
    volatile unsigned int *word = (volatile unsigned int *)0x40u;

    *word = 0x12345678u;
    for (;;) {
    }
}
