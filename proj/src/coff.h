#ifndef COFF_H
#define COFF_H
#include <stdint.h>

// https://wiki.osdev.org/COFF
// http://www.ti.com/lit/an/spraao8/spraao8.pdf
// http://www.skyfree.org/linux/references/coff.pdf
// https://www.virtualbox.org/svn/vbox/trunk/include/iprt/formats/pecoff.h

#ifndef INT8_C
#define INT8_C(x)			(x)
#define UINT8_C(x)			(x)
#define INT16_C(x)			(x)
#define UINT16_C(x)			(x)
#define INT32_C(x)			(x)
#define UINT32_C(x)			(x)
#endif

//
// COFF machine types.
//
#define IMAGE_FILE_MACHINE_UNKNOWN				0
#define IMAGE_FILE_MACHINE_I386					0x014c		// Intel 386.
#define IMAGE_FILE_MACHINE_R3000				0x0162		// MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000				0x0166		// MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000				0x0168		// MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2			0x0169		// MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA				0x0184		// Alpha_AXP
#define IMAGE_FILE_MACHINE_SH3					0x01a2		// SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3DSP				0x01a3
#define IMAGE_FILE_MACHINE_SH3E					0x01a4		// SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4					0x01a6		// SH4 little-endian
#define IMAGE_FILE_MACHINE_SH5					0x01a8		// SH5
#define IMAGE_FILE_MACHINE_ARM					0x01c0		// ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB				0x01c2
#define IMAGE_FILE_MACHINE_AM33					0x01d3
#define IMAGE_FILE_MACHINE_POWERPC				0x01F0		// IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_POWERPCFP			0x01f1
#define IMAGE_FILE_MACHINE_IA64					0x0200		// Intel 64
#define IMAGE_FILE_MACHINE_MIPS16				0x0266		// MIPS
#define IMAGE_FILE_MACHINE_ALPHA64				0x0284		// ALPHA64
#define IMAGE_FILE_MACHINE_MIPSFPU				0x0366		// MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16			0x0466		// MIPS
#define IMAGE_FILE_MACHINE_AXP64				IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE				0x0520		// Infineon
#define IMAGE_FILE_MACHINE_CEF					0x0CEF
#define IMAGE_FILE_MACHINE_EBC					0x0EBC		// EFI Byte Code
#define IMAGE_FILE_MACHINE_AMD64				0x8664		// AMD64 (K8)
#define IMAGE_FILE_MACHINE_M32R					0x9041		// M32R little-endian
#define IMAGE_FILE_MACHINE_CEE					0xC0EE

//
// File header characteristics.
//
#define IMAGE_FILE_RELOCS_STRIPPED				0x0001		// Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE				0x0002		// File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED			0x0004		// Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED			0x0008		// Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM			0x0010		// Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE			0x0020		// App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO			0x0080		// Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE				0x0100		// 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED				0x0200		// Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP		0x0400		// If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP			0x0800		// If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM						0x1000		// System File.
#define IMAGE_FILE_DLL							0x2000		// File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY				0x4000		// File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI			0x8000		// Bytes of machine word are reversed.

#include <pshpack1.h>
struct COFF_FILE_HEADER
{
	uint16_t					Machine;
	uint16_t					NumberOfSections;
	uint32_t					TimeDateStamp;
	uint32_t					PointerToSymbolTable;
	uint32_t					NumberOfSymbols;
	uint16_t					SizeOfOptionalHeader;
	uint16_t					Characteristics;
};
#include <poppack.h>

#include <pshpack1.h>
struct COFF_OPTIONAL_HEADER
{
	uint16_t					Magic;
	uint8_t						MajorLinkerVersion;
	uint8_t						MinorLinkerVersion;
	uint32_t					SizeOfCode;
	uint32_t					SizeOfInitializedData;
	uint32_t					SizeOfUninitializedData;
	uint32_t					AddressOfEntryPoint;
	uint32_t					BaseOfCode;
	uint32_t					BaseOfData;
};
#include <poppack.h>

#include <pshpack1.h>
struct COFF_SECTION_HEADER
{
	char						Name[8];
	uint32_t					VirtualSize;
	uint32_t					VirtualAddress;
	uint32_t					SizeOfRawData;
	uint32_t					PointerToRawData;
	uint32_t					PointerToRelocations;
	uint32_t					PointerToLinenumbers;
	uint16_t					NumberOfRelocations;
	uint16_t					NumberOfLinenumbers;
	uint32_t					Characteristics;
};
#include <poppack.h>

// The size of a COFF_SYMBOL & COFF_AUX_SYMBOL structure.
#define SIZE_OF_COFF_SYMBOL			18

#include <pshpack2.h>
struct COFF_SYMBOL
{
	union
	{
		uint8_t					ShortName[8];
		struct
		{
			uint32_t			Zeroes;
			uint32_t			Offset;
		} LongName;
	};

	uint32_t					Value;
	int16_t						SectionNumber;
	uint16_t					Type;
	uint8_t						StorageClass;
	uint8_t						NumberOfAuxSymbols;
};
#include <poppack.h>

#include <pshpack1.h>

//
// COFF auxiliary symbol token defintion (whatever that is).
//
#include <pshpack2.h>
struct COFF_AUX_SYMBOL_TOKEN_DEF
{
	uint8_t						bAuxType;
	uint8_t						bReserved;
	uint32_t					SymbolTableIndex;
	uint8_t						rgbReserved[12];
};
#include <poppack.h>

//
// COFF auxiliary symbol.
//
#include <pshpack1.h>
union COFF_AUX_SYMBOL
{
	struct
	{
		uint32_t				TagIndex;
		union
		{
			struct
			{
				uint16_t		Linenumber;
				uint16_t		Size;
			} LnSz;
		} Misc;
		union
		{
			struct
			{
				uint32_t		PointerToLinenumber;
				uint32_t		PointerToNextFunction;
			} Function;
			struct
			{
				uint16_t		Dimension[4];
			} Array;
		} FcnAry;
		uint16_t				TvIndex;
	} Sym;

	struct
	{
		uint8_t					Name[SIZE_OF_COFF_SYMBOL];
	} File;

	struct
	{
		uint32_t				Length;
		uint16_t				NumberOfRelocations;
		uint16_t				NumberOfLinenumbers;
		uint32_t				CheckSum;
		uint16_t				Number;
		uint8_t					Selection;
		uint8_t					bReserved;
		uint16_t				HighNumber;
	} Section;

	COFF_AUX_SYMBOL_TOKEN_DEF	TokenDef;
	struct
	{
		uint32_t				crc;
		uint8_t					rgbReserved[14];
	} CRC;
};
#include <poppack.h>

//
// Special COFF section numbers.
//
#define IMAGE_SYM_UNDEFINED						INT16_C(0)
#define IMAGE_SYM_ABSOLUTE						INT16_C(-1)
#define IMAGE_SYM_DEBUG							INT16_C(-2)

//
// COFF symbol storage classes.
//
#define IMAGE_SYM_CLASS_END_OF_FUNCTION			UINT8_C(0xff) // -1
#define IMAGE_SYM_CLASS_NULL					UINT8_C(0)
#define IMAGE_SYM_CLASS_AUTOMATIC				UINT8_C(1)
#define IMAGE_SYM_CLASS_EXTERNAL				UINT8_C(2)
#define IMAGE_SYM_CLASS_STATIC					UINT8_C(3)
#define IMAGE_SYM_CLASS_REGISTER				UINT8_C(4)
#define IMAGE_SYM_CLASS_EXTERNAL_DEF			UINT8_C(5)
#define IMAGE_SYM_CLASS_LABEL					UINT8_C(6)
#define IMAGE_SYM_CLASS_UNDEFINED_LABEL			UINT8_C(7)
#define IMAGE_SYM_CLASS_MEMBER_OF_STRUCT		UINT8_C(8)
#define IMAGE_SYM_CLASS_ARGUMENT				UINT8_C(9)
#define IMAGE_SYM_CLASS_STRUCT_TAG				UINT8_C(10)
#define IMAGE_SYM_CLASS_MEMBER_OF_UNION			UINT8_C(11)
#define IMAGE_SYM_CLASS_UNION_TAG				UINT8_C(12)
#define IMAGE_SYM_CLASS_TYPE_DEFINITION			UINT8_C(13)
#define IMAGE_SYM_CLASS_UNDEFINED_STATIC		UINT8_C(14)
#define IMAGE_SYM_CLASS_ENUM_TAG				UINT8_C(15)
#define IMAGE_SYM_CLASS_MEMBER_OF_ENUM			UINT8_C(16)
#define IMAGE_SYM_CLASS_REGISTER_PARAM			UINT8_C(17)
#define IMAGE_SYM_CLASS_BIT_FIELD				UINT8_C(18)
#define IMAGE_SYM_CLASS_FAR_EXTERNAL			UINT8_C(68)
#define IMAGE_SYM_CLASS_BLOCK					UINT8_C(100)
#define IMAGE_SYM_CLASS_FUNCTION				UINT8_C(101)
#define IMAGE_SYM_CLASS_END_OF_STRUCT			UINT8_C(102)
#define IMAGE_SYM_CLASS_FILE					UINT8_C(103)
#define IMAGE_SYM_CLASS_SECTION					UINT8_C(104)
#define IMAGE_SYM_CLASS_WEAK_EXTERNAL			UINT8_C(105)
#define IMAGE_SYM_CLASS_CLR_TOKEN				UINT8_C(107)

//
// COFF symbol complex types.
//
#define IMAGE_SYM_DTYPE_NULL					UINT16_C(0x0)
#define IMAGE_SYM_DTYPE_POINTER					UINT16_C(0x1)
#define IMAGE_SYM_DTYPE_FUNCTION				UINT16_C(0x2)
#define IMAGE_SYM_DTYPE_ARRAY					UINT16_C(0x3)

//
// COFF Symbol type masks and shift counts.
//
#define N_BTMASK								UINT16_C(0x000f)
#define N_TMASK									UINT16_C(0x0030)
#define N_TMASK1								UINT16_C(0x00c0)
#define N_TMASK2								UINT16_C(0x00f0)
#define N_BTSHFT								4
#define N_TSHIFT								2

//
// COFF Symbol type macros.
//
#define BTYPE(a_Type)							( (a_Type) & N_BTMASK )
#define ISPTR(a_Type)							( ((a_Type) & N_TMASK) == (IMAGE_SYM_DTYPE_POINTER  << N_BTSHFT) )
#define ISFCN(a_Type)							( ((a_Type) & N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION << N_BTSHFT) )
#define ISARY(a_Type)							( ((a_Type) & N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY    << N_BTSHFT) )
#define ISTAG(a_StorageClass)					( (a_StorageClass) == IMAGE_SYM_CLASS_STRUCT_TAG \
													|| (a_StorageClass) == IMAGE_SYM_CLASS_UNION_TAG \
													|| (a_StorageClass) == IMAGE_SYM_CLASS_ENUM_TAG )

//
// Relocation format.
//
struct IMAGE_RELOCATION
{
	union
	{
		uint32_t				VirtualAddress;
		uint32_t				RelocCount;			// Set to the real count when IMAGE_SCN_LNK_NRELOC_OVFL is set
	};
	uint32_t					SymbolTableIndex;
	uint16_t					Type;
};

//
// I386 relocation types.
//
#define IMAGE_REL_I386_ABSOLUTE				0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_I386_DIR16				0x0001  // Direct 16-bit reference to the symbols virtual address
#define IMAGE_REL_I386_REL16				0x0002  // PC-relative 16-bit reference to the symbols virtual address
#define IMAGE_REL_I386_DIR32				0x0006  // Direct 32-bit reference to the symbols virtual address
#define IMAGE_REL_I386_DIR32NB				0x0007  // Direct 32-bit reference to the symbols virtual address, base not included
#define IMAGE_REL_I386_SEG12				0x0009  // Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
#define IMAGE_REL_I386_SECTION				0x000A
#define IMAGE_REL_I386_SECREL				0x000B
#define IMAGE_REL_I386_TOKEN				0x000C  // clr token
#define IMAGE_REL_I386_SECREL7				0x000D  // 7 bit offset from base of section containing target
#define IMAGE_REL_I386_REL32				0x0014  // PC-relative 32-bit reference to the symbols virtual address

//
// MIPS relocation types.
//
#define IMAGE_REL_MIPS_ABSOLUTE				0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_MIPS_REFHALF				0x0001
#define IMAGE_REL_MIPS_REFWORD				0x0002
#define IMAGE_REL_MIPS_JMPADDR				0x0003
#define IMAGE_REL_MIPS_REFHI				0x0004
#define IMAGE_REL_MIPS_REFLO				0x0005
#define IMAGE_REL_MIPS_GPREL				0x0006
#define IMAGE_REL_MIPS_LITERAL				0x0007
#define IMAGE_REL_MIPS_SECTION				0x000A
#define IMAGE_REL_MIPS_SECREL				0x000B
#define IMAGE_REL_MIPS_SECRELLO				0x000C  // Low 16-bit section relative referemce (used for >32k TLS)
#define IMAGE_REL_MIPS_SECRELHI				0x000D  // High 16-bit section relative reference (used for >32k TLS)
#define IMAGE_REL_MIPS_TOKEN				0x000E  // clr token
#define IMAGE_REL_MIPS_JMPADDR16			0x0010
#define IMAGE_REL_MIPS_REFWORDNB			0x0022
#define IMAGE_REL_MIPS_PAIR					0x0025

//
// Alpha relocation types.
//
#define IMAGE_REL_ALPHA_ABSOLUTE			0x0000
#define IMAGE_REL_ALPHA_REFLONG				0x0001
#define IMAGE_REL_ALPHA_REFQUAD				0x0002
#define IMAGE_REL_ALPHA_GPREL32				0x0003
#define IMAGE_REL_ALPHA_LITERAL				0x0004
#define IMAGE_REL_ALPHA_LITUSE				0x0005
#define IMAGE_REL_ALPHA_GPDISP				0x0006
#define IMAGE_REL_ALPHA_BRADDR				0x0007
#define IMAGE_REL_ALPHA_HINT				0x0008
#define IMAGE_REL_ALPHA_INLINE_REFLONG		0x0009
#define IMAGE_REL_ALPHA_REFHI				0x000A
#define IMAGE_REL_ALPHA_REFLO				0x000B
#define IMAGE_REL_ALPHA_PAIR				0x000C
#define IMAGE_REL_ALPHA_MATCH				0x000D
#define IMAGE_REL_ALPHA_SECTION				0x000E
#define IMAGE_REL_ALPHA_SECREL				0x000F
#define IMAGE_REL_ALPHA_REFLONGNB			0x0010
#define IMAGE_REL_ALPHA_SECRELLO			0x0011  // Low 16-bit section relative reference
#define IMAGE_REL_ALPHA_SECRELHI			0x0012  // High 16-bit section relative reference
#define IMAGE_REL_ALPHA_REFQ3				0x0013  // High 16 bits of 48 bit reference
#define IMAGE_REL_ALPHA_REFQ2				0x0014  // Middle 16 bits of 48 bit reference
#define IMAGE_REL_ALPHA_REFQ1				0x0015  // Low 16 bits of 48 bit reference
#define IMAGE_REL_ALPHA_GPRELLO				0x0016  // Low 16-bit GP relative reference
#define IMAGE_REL_ALPHA_GPRELHI				0x0017  // High 16-bit GP relative reference

//
// IBM PowerPC relocation types.
//
#define IMAGE_REL_PPC_ABSOLUTE				0x0000  // NOP
#define IMAGE_REL_PPC_ADDR64				0x0001  // 64-bit address
#define IMAGE_REL_PPC_ADDR32				0x0002  // 32-bit address
#define IMAGE_REL_PPC_ADDR24				0x0003  // 26-bit address, shifted left 2 (branch absolute)
#define IMAGE_REL_PPC_ADDR16				0x0004  // 16-bit address
#define IMAGE_REL_PPC_ADDR14				0x0005  // 16-bit address, shifted left 2 (load doubleword)
#define IMAGE_REL_PPC_REL24					0x0006  // 26-bit PC-relative offset, shifted left 2 (branch relative)
#define IMAGE_REL_PPC_REL14					0x0007  // 16-bit PC-relative offset, shifted left 2 (br cond relative)
#define IMAGE_REL_PPC_TOCREL16				0x0008  // 16-bit offset from TOC base
#define IMAGE_REL_PPC_TOCREL14				0x0009  // 16-bit offset from TOC base, shifted left 2 (load doubleword)

#define IMAGE_REL_PPC_ADDR32NB				0x000A  // 32-bit addr w/o image base
#define IMAGE_REL_PPC_SECREL				0x000B  // va of containing section (as in an image sectionhdr)
#define IMAGE_REL_PPC_SECTION				0x000C  // sectionheader number
#define IMAGE_REL_PPC_IFGLUE				0x000D  // substitute TOC restore instruction iff symbol is glue code
#define IMAGE_REL_PPC_IMGLUE				0x000E  // symbol is glue code; virtual address is TOC restore instruction
#define IMAGE_REL_PPC_SECREL16				0x000F  // va of containing section (limited to 16 bits)
#define IMAGE_REL_PPC_REFHI					0x0010
#define IMAGE_REL_PPC_REFLO					0x0011
#define IMAGE_REL_PPC_PAIR					0x0012
#define IMAGE_REL_PPC_SECRELLO				0x0013  // Low 16-bit section relative reference (used for >32k TLS)
#define IMAGE_REL_PPC_SECRELHI				0x0014  // High 16-bit section relative reference (used for >32k TLS)
#define IMAGE_REL_PPC_GPREL					0x0015
#define IMAGE_REL_PPC_TOKEN					0x0016  // clr token

#define IMAGE_REL_PPC_TYPEMASK				0x00FF  // mask to isolate above values in IMAGE_RELOCATION.Type

// Flag bits in IMAGE_RELOCATION.TYPE

#define IMAGE_REL_PPC_NEG					0x0100  // subtract reloc value rather than adding it
#define IMAGE_REL_PPC_BRTAKEN				0x0200  // fix branch prediction bit to predict branch taken
#define IMAGE_REL_PPC_BRNTAKEN				0x0400  // fix branch prediction bit to predict branch not taken
#define IMAGE_REL_PPC_TOCDEFN				0x0800  // toc slot defined in file (or, data in toc)

//
// Hitachi SH3 relocation types.
//
#define IMAGE_REL_SH3_ABSOLUTE				0x0000  // No relocation
#define IMAGE_REL_SH3_DIRECT16				0x0001  // 16 bit direct
#define IMAGE_REL_SH3_DIRECT32				0x0002  // 32 bit direct
#define IMAGE_REL_SH3_DIRECT8				0x0003  // 8 bit direct, -128..255
#define IMAGE_REL_SH3_DIRECT8_WORD			0x0004  // 8 bit direct .W (0 ext.)
#define IMAGE_REL_SH3_DIRECT8_LONG			0x0005  // 8 bit direct .L (0 ext.)
#define IMAGE_REL_SH3_DIRECT4				0x0006  // 4 bit direct (0 ext.)
#define IMAGE_REL_SH3_DIRECT4_WORD			0x0007  // 4 bit direct .W (0 ext.)
#define IMAGE_REL_SH3_DIRECT4_LONG			0x0008  // 4 bit direct .L (0 ext.)
#define IMAGE_REL_SH3_PCREL8_WORD			0x0009  // 8 bit PC relative .W
#define IMAGE_REL_SH3_PCREL8_LONG			0x000A  // 8 bit PC relative .L
#define IMAGE_REL_SH3_PCREL12_WORD			0x000B  // 12 LSB PC relative .W
#define IMAGE_REL_SH3_STARTOF_SECTION		0x000C  // Start of EXE section
#define IMAGE_REL_SH3_SIZEOF_SECTION		0x000D  // Size of EXE section
#define IMAGE_REL_SH3_SECTION				0x000E  // Section table index
#define IMAGE_REL_SH3_SECREL				0x000F  // Offset within section
#define IMAGE_REL_SH3_DIRECT32_NB			0x0010  // 32 bit direct not based
#define IMAGE_REL_SH3_GPREL4_LONG			0x0011  // GP-relative addressing
#define IMAGE_REL_SH3_TOKEN					0x0012  // clr token
#define IMAGE_REL_SHM_PCRELPT				0x0013  // Offset from current
													//  instruction in longwords
													//  if not NOMODE, insert the
													//  inverse of the low bit at
													//  bit 32 to select PTA/PTB
#define IMAGE_REL_SHM_REFLO					0x0014  // Low bits of 32-bit address
#define IMAGE_REL_SHM_REFHALF				0x0015  // High bits of 32-bit address
#define IMAGE_REL_SHM_RELLO					0x0016  // Low bits of relative reference
#define IMAGE_REL_SHM_RELHALF				0x0017  // High bits of relative reference
#define IMAGE_REL_SHM_PAIR					0x0018  // offset operand for relocation

#define IMAGE_REL_SH_NOMODE					0x8000  // relocation ignores section mode

//
// ARM relocation types.
//
#define IMAGE_REL_ARM_ABSOLUTE				0x0000  // No relocation required
#define IMAGE_REL_ARM_ADDR32				0x0001  // 32 bit address
#define IMAGE_REL_ARM_ADDR32NB				0x0002  // 32 bit address w/o image base
#define IMAGE_REL_ARM_BRANCH24				0x0003  // 24 bit offset << 2 & sign ext.
#define IMAGE_REL_ARM_BRANCH11				0x0004  // Thumb: 2 11 bit offsets
#define IMAGE_REL_ARM_TOKEN					0x0005  // clr token
#define IMAGE_REL_ARM_GPREL12				0x0006  // GP-relative addressing (ARM)
#define IMAGE_REL_ARM_GPREL7				0x0007  // GP-relative addressing (Thumb)
#define IMAGE_REL_ARM_BLX24					0x0008
#define IMAGE_REL_ARM_BLX11					0x0009
#define IMAGE_REL_ARM_SECTION				0x000E  // Section table index
#define IMAGE_REL_ARM_SECREL				0x000F  // Offset within section

#define IMAGE_REL_AM_ABSOLUTE				0x0000
#define IMAGE_REL_AM_ADDR32					0x0001
#define IMAGE_REL_AM_ADDR32NB				0x0002
#define IMAGE_REL_AM_CALL32					0x0003
#define IMAGE_REL_AM_FUNCINFO				0x0004
#define IMAGE_REL_AM_REL32_1				0x0005
#define IMAGE_REL_AM_REL32_2				0x0006
#define IMAGE_REL_AM_SECREL					0x0007
#define IMAGE_REL_AM_SECTION				0x0008
#define IMAGE_REL_AM_TOKEN					0x0009

//
// x64 relocations
//
#define IMAGE_REL_AMD64_ABSOLUTE			0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_AMD64_ADDR64				0x0001  // 64-bit address (VA).
#define IMAGE_REL_AMD64_ADDR32				0x0002  // 32-bit address (VA).
#define IMAGE_REL_AMD64_ADDR32NB			0x0003  // 32-bit address w/o image base (RVA).
#define IMAGE_REL_AMD64_REL32				0x0004  // 32-bit relative address from byte following reloc
#define IMAGE_REL_AMD64_REL32_1				0x0005  // 32-bit relative address from byte distance 1 from reloc
#define IMAGE_REL_AMD64_REL32_2				0x0006  // 32-bit relative address from byte distance 2 from reloc
#define IMAGE_REL_AMD64_REL32_3				0x0007  // 32-bit relative address from byte distance 3 from reloc
#define IMAGE_REL_AMD64_REL32_4				0x0008  // 32-bit relative address from byte distance 4 from reloc
#define IMAGE_REL_AMD64_REL32_5				0x0009  // 32-bit relative address from byte distance 5 from reloc
#define IMAGE_REL_AMD64_SECTION				0x000A  // Section index
#define IMAGE_REL_AMD64_SECREL				0x000B  // 32 bit offset from base of section containing target
#define IMAGE_REL_AMD64_SECREL7				0x000C  // 7 bit unsigned offset from base of section containing target
#define IMAGE_REL_AMD64_TOKEN				0x000D  // 32 bit metadata token
#define IMAGE_REL_AMD64_SREL32				0x000E  // 32 bit signed span-dependent value emitted into object
#define IMAGE_REL_AMD64_PAIR				0x000F
#define IMAGE_REL_AMD64_SSPAN32				0x0010  // 32 bit signed span-dependent value applied at link time

//
// IA64 relocation types.
//
#define IMAGE_REL_IA64_ABSOLUTE				0x0000
#define IMAGE_REL_IA64_IMM14				0x0001
#define IMAGE_REL_IA64_IMM22				0x0002
#define IMAGE_REL_IA64_IMM64				0x0003
#define IMAGE_REL_IA64_DIR32				0x0004
#define IMAGE_REL_IA64_DIR64				0x0005
#define IMAGE_REL_IA64_PCREL21B				0x0006
#define IMAGE_REL_IA64_PCREL21M				0x0007
#define IMAGE_REL_IA64_PCREL21F				0x0008
#define IMAGE_REL_IA64_GPREL22				0x0009
#define IMAGE_REL_IA64_LTOFF22				0x000A
#define IMAGE_REL_IA64_SECTION				0x000B
#define IMAGE_REL_IA64_SECREL22				0x000C
#define IMAGE_REL_IA64_SECREL64I			0x000D
#define IMAGE_REL_IA64_SECREL32				0x000E
//
#define IMAGE_REL_IA64_DIR32NB				0x0010
#define IMAGE_REL_IA64_SREL14				0x0011
#define IMAGE_REL_IA64_SREL22				0x0012
#define IMAGE_REL_IA64_SREL32				0x0013
#define IMAGE_REL_IA64_UREL32				0x0014
#define IMAGE_REL_IA64_PCREL60X				0x0015  // This is always a BRL and never converted
#define IMAGE_REL_IA64_PCREL60B				0x0016  // If possible, convert to MBB bundle with NOP.B in slot 1
#define IMAGE_REL_IA64_PCREL60F				0x0017  // If possible, convert to MFB bundle with NOP.F in slot 1
#define IMAGE_REL_IA64_PCREL60I				0x0018  // If possible, convert to MIB bundle with NOP.I in slot 1
#define IMAGE_REL_IA64_PCREL60M				0x0019  // If possible, convert to MMB bundle with NOP.M in slot 1
#define IMAGE_REL_IA64_IMMGPREL64			0x001A
#define IMAGE_REL_IA64_TOKEN				0x001B  // clr token
#define IMAGE_REL_IA64_GPREL32				0x001C
#define IMAGE_REL_IA64_ADDEND				0x001F

//
// CEF relocation types.
//
#define IMAGE_REL_CEF_ABSOLUTE				0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_CEF_ADDR32				0x0001  // 32-bit address (VA).
#define IMAGE_REL_CEF_ADDR64				0x0002  // 64-bit address (VA).
#define IMAGE_REL_CEF_ADDR32NB				0x0003  // 32-bit address w/o image base (RVA).
#define IMAGE_REL_CEF_SECTION				0x0004  // Section index
#define IMAGE_REL_CEF_SECREL				0x0005  // 32 bit offset from base of section containing target
#define IMAGE_REL_CEF_TOKEN					0x0006  // 32 bit metadata token

//
// clr relocation types.
//
#define IMAGE_REL_CEE_ABSOLUTE				0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_CEE_ADDR32				0x0001  // 32-bit address (VA).
#define IMAGE_REL_CEE_ADDR64				0x0002  // 64-bit address (VA).
#define IMAGE_REL_CEE_ADDR32NB				0x0003  // 32-bit address w/o image base (RVA).
#define IMAGE_REL_CEE_SECTION				0x0004  // Section index
#define IMAGE_REL_CEE_SECREL				0x0005  // 32 bit offset from base of section containing target
#define IMAGE_REL_CEE_TOKEN					0x0006  // 32 bit metadata token


#define IMAGE_REL_M32R_ABSOLUTE				0x0000  // No relocation required
#define IMAGE_REL_M32R_ADDR32				0x0001  // 32 bit address
#define IMAGE_REL_M32R_ADDR32NB				0x0002  // 32 bit address w/o image base
#define IMAGE_REL_M32R_ADDR24				0x0003  // 24 bit address
#define IMAGE_REL_M32R_GPREL16				0x0004  // GP relative addressing
#define IMAGE_REL_M32R_PCREL24				0x0005  // 24 bit offset << 2 & sign ext.
#define IMAGE_REL_M32R_PCREL16				0x0006  // 16 bit offset << 2 & sign ext.
#define IMAGE_REL_M32R_PCREL8				0x0007  // 8 bit offset << 2 & sign ext.
#define IMAGE_REL_M32R_REFHALF				0x0008  // 16 MSBs
#define IMAGE_REL_M32R_REFHI				0x0009  // 16 MSBs; adj for LSB sign ext.
#define IMAGE_REL_M32R_REFLO				0x000A  // 16 LSBs
#define IMAGE_REL_M32R_PAIR					0x000B  // Link HI and LO
#define IMAGE_REL_M32R_SECTION				0x000C  // Section table index
#define IMAGE_REL_M32R_SECREL32				0x000D  // 32 bit section relative reference
#define IMAGE_REL_M32R_TOKEN				0x000E  // clr token

#define IMAGE_REL_EBC_ABSOLUTE				0x0000  // No relocation required
#define IMAGE_REL_EBC_ADDR32NB				0x0001  // 32 bit address w/o image base
#define IMAGE_REL_EBC_REL32					0x0002  // 32-bit relative address from byte following reloc
#define IMAGE_REL_EBC_SECTION				0x0003  // Section table index
#define IMAGE_REL_EBC_SECREL				0x0004  // Offset within section

//
// Line number format.
//
#include <pshpack1.h>
struct IMAGE_LINENUMBER
{
	union
	{
		uint32_t				SymbolTableIndex;		// Symbol table index of function name if Linenumber is 0.
		uint32_t				VirtualAddress;			// Virtual address of line number.
	} Type;
	uint16_t					Linenumber;				// Line number.
};
#include <poppack.h>

#endif // COFF_H
