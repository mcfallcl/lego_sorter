#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define BUFFER_SIZE 19

int main()
{
	int file;
	printf("Starting i2c test\n");

	if ((file=open("/dev/i2c-1", O_RDWR)) < 0) {
		perror("Failed to open i2c bus\n");
		return 1;
	}

	int ret = ioctl(file, I2C_SLAVE, 0x55);
	if (ret < 0) {
		perror("Failed to connect to Arduino\n");
		return 1;
	}

	char writeBuffer = 0;
	char buf = 0;
	printf("buf = %d\n", buf);
	for (; writeBuffer < 255; writeBuffer = (writeBuffer << 1) + 1) {
		if (write(file, &writeBuffer, 1) != 1) {
			perror("Failed to write to bus\n");
			return 1;
		}
		printf("Sent %X\n", writeBuffer);
		if (read(file, &buf, 1) != 1) {
			perror("Failed to read from the bus\n");
			return 1;
		}
		printf("Received %X\n", buf);
	}

	return 0;
}
