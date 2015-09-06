void kernel_main(void) {
	const char *bootmsg = "First booting kernel of ArnavOS.";
	char *vidptr = (char*)0xb8000;
	unsigned int i = 0;
	unsigned int j = 0;

	while(j < 80 * 25 * 2) {
		vidptr[j] = ' ';
		vidptr[j + 1] = 0x07;
		j = j + 2;
	}

	j = 0;

	while(bootmsg[j] != '\0') {
		vidptr[i] = bootmsg[j];
		vidptr[i + 1] = 0x07;
		j++;
		i = i + 2;
	}
	return;
}