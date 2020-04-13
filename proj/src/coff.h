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

#endif // COFF_H
