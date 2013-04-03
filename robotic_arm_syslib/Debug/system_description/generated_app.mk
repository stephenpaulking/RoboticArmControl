# generated_app.mk
#
# Machine generated for a CPU named "cpu" as defined in:
# /home/netlab/s2king/quartus_project/DE0_SOPC.ptf
#
# Generated: 2013-04-03 12:24:52.401

# DO NOT MODIFY THIS FILE
#
#   Changing this file will have subtle consequences
#   which will almost certainly lead to a nonfunctioning
#   system. If you do modify this file, be aware that your
#   changes will be overwritten and lost when this file
#   is generated again.
#
# DO NOT MODIFY THIS FILE

# assuming the Quartus project directory is the same as the PTF directory
QUARTUS_PROJECT_DIR = /home/netlab/s2king/quartus_project

# the simulation directory is a subdirectory of the PTF directory
SIMDIR = $(QUARTUS_PROJECT_DIR)/DE0_SOPC_sim

DBL_QUOTE := "


# macros defined by/for onchip_mem, cfi_flash, & sdram
PAD_DAT_FILES = --pad=0
CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX = $(CFI_FLASH_FLASHTARGET_TMP1:0=)
CFI_FLASH_FLASHTARGET_TMP1 = $(ALT_SIM_OPTIMIZE:1=RUN_ON_HDL_SIMULATOR_ONLY_)
BOOT_COPIER = boot_loader_cfi.srec
CPU_CLASS = altera_nios2
CPU_RESET_ADDRESS = 0x2808000


all: dat delete_placeholder_warning hex sym flashfiles

dat: $(SIMDIR)/onchip_mem.dat $(SIMDIR)/cfi_flash.dat $(SIMDIR)/sdram.dat
.PHONY: dat

delete_placeholder_warning: do_delete_placeholder_warning
.PHONY: delete_placeholder_warning

hex: $(QUARTUS_PROJECT_DIR)/onchip_mem.hex
.PHONY: hex

sym: $(SIMDIR)/onchip_mem.sym $(SIMDIR)/cfi_flash.sym $(SIMDIR)/sdram.sym
.PHONY: sym

verifysysid: dummy_verifysysid_file
.PHONY: verifysysid

flashfiles: $(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash
.PHONY: flashfiles

$(SIMDIR)/onchip_mem.dat: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	elf2dat --infile=$(ELF) --outfile=$(SIMDIR)/onchip_mem.dat --base=0x02808000 --end=0x280F7FF $(PAD_DAT_FILES) --create-lanes=0 --width=32

$(SIMDIR)/cfi_flash.dat: $(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	flash2dat --infile=$(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash --outfile=$(SIMDIR)/cfi_flash.dat --base=0x02400000 --end=0x27FFFFF $(PAD_DAT_FILES) --create-lanes=1 --width=16 --relocate-input=0x02400000

$(SIMDIR)/sdram.dat: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	elf2dat --infile=$(ELF) --outfile=$(SIMDIR)/sdram.dat --base=0x01800000 --end=0x1FFFFFF $(PAD_DAT_FILES) --create-lanes=0 --width=16

do_delete_placeholder_warning:
	rm -f $(SIMDIR)/contents_file_warning.txt
.PHONY: do_delete_placeholder_warning

$(QUARTUS_PROJECT_DIR)/onchip_mem.hex: $(ELF)
	@echo Post-processing to create $(notdir $@)
	elf2hex $(ELF) 0x02808000 0x280F7FF --width=32 $(QUARTUS_PROJECT_DIR)/onchip_mem.hex --create-lanes=0

$(SIMDIR)/onchip_mem.sym: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	nios2-elf-nm -n $(ELF) > $(SIMDIR)/onchip_mem.sym

$(SIMDIR)/cfi_flash.sym: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	nios2-elf-nm -n $(ELF) > $(SIMDIR)/cfi_flash.sym

$(SIMDIR)/sdram.sym: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Post-processing to create $(notdir $@)
	nios2-elf-nm -n $(ELF) > $(SIMDIR)/sdram.sym

dummy_verifysysid_file:
	nios2-download $(JTAG_CABLE)                                --sidp=0x000000e0 --id=0 --timestamp=1363684272
.PHONY: dummy_verifysysid_file

$(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash: $(ELF)
	@echo Post-processing to create $(notdir $@)
	elf2flash --input=$(ELF) --flash= --boot=$(DBL_QUOTE)$(shell $(DBL_QUOTE)$(QUARTUS_ROOTDIR)/sopc_builder/bin/find_sopc_component_dir$(DBL_QUOTE) $(CPU_CLASS) $(QUARTUS_PROJECT_DIR))/$(BOOT_COPIER)$(DBL_QUOTE) --outfile=$(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash --sim_optimize=$(ALT_SIM_OPTIMIZE) --base=0x2400000 --end=0x27FFFFF --reset=$(CPU_RESET_ADDRESS)


generated_app_clean:
	$(RM) $(SIMDIR)/onchip_mem.dat
	$(RM) $(SIMDIR)/cfi_flash.dat
	$(RM) $(SIMDIR)/sdram.dat
	$(RM) $(QUARTUS_PROJECT_DIR)/onchip_mem.hex
	$(RM) $(SIMDIR)/onchip_mem.sym
	$(RM) $(SIMDIR)/cfi_flash.sym
	$(RM) $(SIMDIR)/sdram.sym
	$(RM) $(CFI_FLASH_FLASHTARGET_ALT_SIM_PREFIX)cfi_flash.flash
.PHONY: generated_app_clean
