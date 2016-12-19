#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <direct.h>
#include <io.h>

// 33 images need to be copyed
#define		IMG_COUNT	33

// which model
char mod[20] = "0001";

char ver[20] = "";

// project name, D1C or PLT or others
char proj_name[20] = "PLT";

// top directory of your source code
// ex: \\10.206.25.230\home\quan\Documents\d1c_2006_after_build
char *top = "";

// copy images to which directory
char *dst = "";

// rename images or not
BOOL rename_imgs = TRUE;

// all the images path
char *path[IMG_COUNT];

void usage(char *prog) {
	printf("Usage: %s -v <version> [options] <top-src-dir> <dst-dir>\n", prog);
	printf("Copy all the images you built under <top-src-dir> to <dst-dir>\n\n");
	printf("  -v <version>:  Major version and minor version, must be 4 digit.\n");
	printf("                 This option is Mandatory.\n");
	printf("  -m <model>:    Model name, 0001 by default\n");
	printf("  -p <proj>:     Project name, PLT by default\n");
	printf("  -r:            Do not rename images, will rename images by default.\n");
	printf("\n<top-src-dir> is the root directory of your source code, <dst-dir> is \n\
the direcory where you want copy images to. If the <dst-dir> do not \n\
exist, it will be created. These two arguments are Mandatory.\n\n");
	printf("ex: %s -v 2222 -m 00WW \\\\IP\\path\\to\\source PLT\n",
		prog);
}

void handle_opts(int argc, char **argv) {
	// require 5 parameter at least
	// program name, -v option and its argument, src and dst directory
	int para_required = 5;
	char *prog = argv[0];
	// Skip argv[0]
	argv++;

	while (*argv && argc >= para_required) {
		if (!strcmp(*argv, "-v")) {
			argv++;
			strcpy_s(ver, strlen(*argv) + 1, *argv);
			//para_required += 2;
		}
		else if (!strcmp(*argv, "-m")) {
			argv++;
			strcpy_s(mod, strlen(*argv) + 1, *argv);
			para_required += 2;
		}
		else if (!strcmp(*argv, "-r")) {
			rename_imgs = FALSE;
			para_required++;
		}
		else if (!strcmp(*argv, "-p")) {
			argv++;
			strcpy_s(proj_name, strlen(*argv) + 1, *argv);
			para_required += 2;
		}
		else {
			break;
		}
		argv++;
	}

	if (argc != para_required || ver[0] == '\0') {
		usage(prog);
		exit(1);
	}

	top = *argv;
	argv++;
	dst = *argv;

	if (_access(dst, 0) != 0) {
		printf("making directory %s\n", dst);
		_mkdir(dst);
	}
}

char* allocate_mem(char *path) {
	size_t s = strlen(path) + 1;
	char *buffer = (char *)malloc(s);
	strcpy_s(buffer, s, path);
	return buffer;
}

void make_image_path() {
	char buffer[1000];
	char *mid_part = "\\TZ.BF.4.0.5\\trustzone_images\\build\\ms\\bin\\ZALAANAA\\";

	// trustzone imags
	snprintf(buffer, 1000, "%s%scmnlib.mbn", top, mid_part);
	path[0] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%scmnlib64.mbn", top, mid_part);
	path[1] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%skeymaster.mbn", top, mid_part);
	path[2] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%slksecapp.mbn", top, mid_part);
	path[3] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%stz.mbn", top, mid_part);
	path[4] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%sdevcfg.mbn", top, mid_part);
	path[5] = allocate_mem(buffer);

	// Boot images
	mid_part = "\\BOOT.BF.3.3\\boot_images\\core\\storage\\tools\\ptool\\";
	snprintf(buffer, 1000, "%s%sgpt_main0.bin", top, mid_part);
	path[6] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%sgpt_backup0.bin", top, mid_part);
	path[7] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%sgpt_both0.bin", top, mid_part);
	path[8] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%spatch0.xml", top, mid_part);
	path[9] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%srawprogram0.xml", top, mid_part);
	path[10] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%srawprogram0_BLANK.xml", top, mid_part);
	path[11] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%szeros_1sector.bin", top, mid_part);
	path[12] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%szeros_33sectors.bin", top, mid_part);
	path[13] = allocate_mem(buffer);
	mid_part = "\\BOOT.BF.3.3\\boot_images\\build\\ms\\bin\\FAASANAZ\\";
	snprintf(buffer, 1000, "%s%ssbl1.mbn", top, mid_part);
	path[14] = allocate_mem(buffer);
	mid_part = "\\BOOT.BF.3.3\\boot_images\\build\\ms\\bin\\FAADANAZ\\";
	snprintf(buffer, 1000, "%s%sprog_emmc_firehose_8937_ddr.mbn", top, mid_part);
	path[15] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%sprog_emmc_firehose_8937_lite.mbn", top, mid_part);
	path[16] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%svalidated_emmc_firehose_8937_ddr.mbn", top, mid_part);
	path[17] = allocate_mem(buffer);

	//MSM8937
	mid_part = "\\MSM8937\\common\\build\\bin\\asic\\";
	snprintf(buffer, 1000, "%s%sNON-HLOS.bin", top, mid_part);
	path[18] = allocate_mem(buffer);
	mid_part = "\\MSM8937\\common\\sectools\\resources\\build\\fileversion2\\";
	snprintf(buffer, 1000, "%s%ssec.dat", top, mid_part);
	path[19] = allocate_mem(buffer);

	//ADSP
	mid_part = "\\ADSP.8953.2.8.2\\adsp_proc\\build\\dynamic_signed\\8937\\";
	snprintf(buffer, 1000, "%s%sadspso.bin", top, mid_part);
	path[20] = allocate_mem(buffer);

	//RPM
	mid_part = "\\RPM.BF.2.2\\rpm_proc\\build\\ms\\bin\\8937\\";
	snprintf(buffer, 1000, "%s%srpm.mbn", top, mid_part);
	path[21] = allocate_mem(buffer);

	//FTM
	snprintf(buffer, 1000, "%s\\FTM\\out\\ftm.img", top);
	path[22] = allocate_mem(buffer);

	//aboot
	snprintf(buffer, 1000, "%s\\LINUX\\out_img\\%s\\%s-0-%s-emmc_appsboot.mbn",
		top, proj_name, proj_name, ver);
	path[23] = allocate_mem(buffer);

	// userdata.img
	mid_part = "\\LINUX\\android\\out\\target\\product\\";
	snprintf(buffer, 1000, "%s%s%s\\userdata.img", top, mid_part, proj_name);
	path[24] = allocate_mem(buffer);

	// other ap imgs
	mid_part = "\\LINUX\\out_img\\";
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-0001-boot.img", top, mid_part, proj_name, proj_name, ver);
	path[25] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-0001-cache.img", top, mid_part, proj_name, proj_name, ver);
	path[26] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-mdtp.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[27] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-persist.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[28] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-ramdisk.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[29] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-ramdisk-recovery.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[30] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-recovery.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[31] = allocate_mem(buffer);
	snprintf(buffer, 1000, "%s%s%s\\%s-0-%s-%s-system.img", top, mid_part, proj_name, proj_name, ver, mod);
	path[32] = allocate_mem(buffer);
	// print();
}

void get_base_name(char *name, char *path) {
	size_t s = strlen(path);
	path += s;
	while (*path != '\\') path--;
	path++;
	strcpy_s(name, strlen(path) + 1, path);
}

void make_new_file_name(char *new_name, char *base_name) {
	snprintf(new_name, 1000, "%s\\%s", dst, base_name);
}

void copy() {
	for (int i = 0; i < IMG_COUNT; i++) {
		char new_name[1000] = "";
		char base_name[100] = "";

		// test existence
		if (_access(path[i], 0) != 0) {
			printf("\nFILE %s DOES NOT EXIST !\n\n", path[i]);
			continue;
		}

		get_base_name(base_name, path[i]);
		make_new_file_name(new_name, base_name);
		printf("Copying file %s...\n", base_name);
		int ret = CopyFileA(path[i], new_name, FALSE);
		if (!ret)
			printf("\nCOPYING FILE %s FAILED !\n\n", base_name);
	}
}

void free_mem(void) {
	for (int i = 0; i < IMG_COUNT; i++)
		if (path[i])
			free(path[i]);
}

void do_rename() {
	// change working directory to dest directory
	_chdir(dst);
	char *names[] = {
		"system.img", "ramdisk.img", "persist.img",
		"mdtp.img", "ramdisk-recovery.img", "recovery.img" };
	char full_name[100];
	for (int i = 0; i < sizeof names / sizeof names[0]; i++) {
		snprintf(full_name, 100, "%s-0-%s-%s-%s", proj_name, ver, mod, names[i]);
		if (!_access(full_name, 0)) {
			printf("Rename %s to %s\n", full_name, names[i]);
			rename(full_name, names[i]);
		}
	}
	// boot.img
	snprintf(full_name, 100, "%s-0-%s-0001-boot.img", proj_name, ver);
	if (!_access(full_name, 0)) {
		printf("Rename %s to %s\n", full_name, "boot.img");
		rename(full_name, "boot.img");
	}
	// cache.img
	snprintf(full_name, 100, "%s-0-%s-0001-cache.img", proj_name, ver);
	if (!_access(full_name, 0)) {
		printf("Rename %s to %s\n", full_name, "cache.img");
		rename(full_name, "cache.img");
	}
	// aboot
	snprintf(full_name, 100, "%s-0-%s-emmc_appsboot.mbn", proj_name, ver);
	if (!_access(full_name, 0)) {
		printf("Rename %s to %s\n", full_name, "emmc_appsboot.mbn");
		rename(full_name, "emmc_appsboot.mbn");
	}
}

int main(int argc, char *argv[]) {
	handle_opts(argc, argv);
	make_image_path();
	atexit(free_mem);
	copy();
	if (rename_imgs)
		do_rename();

	return 0;
}