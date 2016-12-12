#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 33 images need to be copyed
#define		COUNT	33

// which model
char *mod = "00WW";

// which version? major version and minor version
char *ver = NULL;

// project name, D1C or PLT or others
char proj[10] = "";

// image name prefix, D1C or PLT or others
char *img_name_prfix = "";

// top directory of your source code
// ex: \\10.206.25.230\home\quan\Documents\d1c_2006_after_build
char *top = "";

// copy images to which directory
char *dst = "";

// all the images path
char *path[COUNT];

void usage(char *prog_name) {
	printf("Usage: %s [options] <top-src-dir> <dst-dir>\n", prog_name);
	printf("Copy all the images you built under top-src-dir to dst-dir\n\n");
	printf("  -v: major version and minor version, must be 4 digit\n");
	printf("  -m: model name\n");
	printf("ex: %s -v 2222 -m 00WW \\\\10.206.25.230\\home\\quan\\Documents\\PLT PLT\n",
		prog_name);
}

void handle_opts(int argc, char **argv) {
	printf("argc: %d\n", argc);
	// require 3 parameter at least
	int para_required = 3;
	char *prog_name = argv[0];
	// Skip argv[0]
	argv++;

	while (*argv) {
		if (!strcmp(*argv, "-v")) {
			argv++;
			ver = *argv;
			para_required += 2;
		}
		else if (!strcmp(*argv, "-m")) {
			argv++;
			mod = *argv;
			para_required += 2;
		}
		else {
			break;
		}
		argv++;
	}
	printf("para_required: %d\n", para_required);
	if (argc != para_required) {
		usage(prog_name);
		exit(0);
	}
	top = *argv;
	argv++;
	dst = *argv;
}

char *add_backslash(char *path) {
	char *transfered, *tmp = path;
	int count = 0;
	while (*path) {
		if (*path == '\\')
			count++;
		path++;
	}
	transfered = (char *) malloc(strlen(path) + count + 1);
	char *trans = transfered;
	while (*tmp) {
		*trans = *tmp;
		if (*tmp = '\\') {
			trans++;
			*trans = '\\';
		}
		trans++;
		tmp++;
	}
	*trans = '\0';
	return transfered;
}

void print() {
	for (int i = 0; i < COUNT; i++) {
		printf("%s\n", path[i]);
	}
}

void make_image_path() {
	char buffer[1000];
	char *mid_part = "\\TZ.BF.4.0.5\\trustzone_images\\build\\ms\\bin\\ZALAANAA\\";
	// trustzone imags
	snprintf(buffer, 1000, "%s%scmnlib.mbn", top, mid_part);
	printf("buffer: %s\n", buffer);
	path[0] = add_backslash(buffer);
	snprintf(buffer,1000, "%s%scmnlib64.mbn", top, mid_part);
	path[1] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%skeymaster.mbn", top, mid_part);
	path[2] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%slksecapp.mbn", top, mid_part);
	path[3] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%stz.mbn", top, mid_part);
	path[4] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%sdevcfg.mbn", top, mid_part);
	path[5] = add_backslash(buffer);

	// Boot images
	mid_part = "\\BOOT.BF.3.3\\boot_images\\core\\storage\\tools\\ptool\\";
	snprintf(buffer, 1000, "%s%sgpt_main0.bin", top, mid_part);
	path[6] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%sgpt_backup0.bin", top, mid_part);
	path[7] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%sgpt_both0.bin", top, mid_part);
	path[8] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%spath0.xml", top, mid_part);
	path[9] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%srawprogram0.xml", top, mid_part);
	path[10] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%srawprogram0_BLANK.XML", top, mid_part);
	path[11] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%szeros_1sector.bin", top, mid_part);
	path[12] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%szeros_33sectors.bin", top, mid_part);
	path[13] = add_backslash(buffer);
	mid_part = "\\BOOT.BF.3.3\\boot_images\\build\\ms\\bin\\FAASANAZ\\";
	snprintf(buffer, 1000, "%s%ssbl1.mbn", top, mid_part);
	path[14] = add_backslash(buffer);
	mid_part = "\\BOOT.BF.3.3\\boot_images\\build\\ms\\bin\\FAADANAZ\\";
	snprintf(buffer, 1000, "%s%sprog_emmc_firehose_8937_ddr.mbn", top, mid_part);
	path[15] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%sprog_emmc_firehose_8937_lite.mbn", top, mid_part);
	path[16] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%svalidated_emmc_firehose_8937_ddr.mbn", top, mid_part);
	path[17] = add_backslash(buffer);

	//MSM8937
	mid_part = "\\MSM8937\\common\\build\\bin\\asic\\";
	snprintf(buffer, 1000, "%s%sNON-HLOS.bin", top, mid_part);
	path[18] = add_backslash(buffer);
	mid_part = "\\MSM8937\\common\\sectools\\resources\\build\\fileversion2\\";
	snprintf(buffer, 1000, "%s%ssec.dat", top, mid_part);
	path[19] = add_backslash(buffer);

	//ADSP
	mid_part = "\\ADSP.8953.2.8.2\\adsp_proc\\build\\dynamic_signed\\8937\\";
	snprintf(buffer, 1000, "%s%sadspso.bin", top, mid_part);
	path[20] = add_backslash(buffer);

	//RPM
	mid_part = "\\RPM.BF.2.2\\rpm_proc\\build\\ms\\bin\\8937\\";
	snprintf(buffer, 1000, "%s%srpm.mbn", top, mid_part);
	path[21] = add_backslash(buffer);

	//FTM
	snprintf(buffer, 1000, "%s\\FTM\\out\\ftm.img", top);
	path[22] = add_backslash(buffer);

	//aboot
	snprintf(buffer, 1000, "%s\\LINUX\\out_img\\%s\\%s-0-%s-emmc_appsboot.mbn",
		top, proj, proj, ver);
	path[23] = add_backslash(buffer);

	// userdata.img
	mid_part = "\\LINUX\\android\\out\\target\\product\\";
	snprintf(buffer, 1000, "%s%s%s\\userdata.img", top, mid_part, proj);
	path[24] = add_backslash(buffer);

	// other ap imgs
	mid_part = "\\LINUX\\out_img\\";
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-0001-boot.img", top, mid_part, proj, proj, ver);
	path[25] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-0001-cache.img", top, mid_part, proj, proj, ver);
	path[26] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-mdtp.img", top, mid_part, proj, proj, ver, mod);
	path[27] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-persist.img", top, mid_part, proj, proj, ver, mod);
	path[28] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-ramdisk.img", top, mid_part, proj, proj, ver, mod);
	path[29] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-ramdisk-recovery.img", top, mid_part, proj, proj, ver, mod);
	path[30] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-recovery.img", top, mid_part, proj, proj, ver, mod);
	path[31] = add_backslash(buffer);
	snprintf(buffer, 1000, "%s%s\\%s\\%s-0-%s-%s-system.img", top, mid_part, proj, proj, ver, mod);
	path[32] = add_backslash(buffer);
	print();
}

void copy() {

}



int main(int argc, char *argv[]) {
	handle_opts(argc, argv);
	make_image_path();
	if (argc < 3)
		usage(argv[0]);
	else
		copy();

	return 0;
}