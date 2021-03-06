/**
 * libdmtx - Data Matrix Encoding/Decoding Library
 * Copyright 2008, 2009 Mike Laughton. All rights reserved.
 *
 * See LICENSE file in the main project directory for full
 * terms of use and distribution.
 *
 * Contact: Mike Laughton <mike@dragonflylogic.com>
 *
 * \file dmtxstatic.h
 * \brief Static header
 */

#ifndef __DMTXSTATIC_H__
#define __DMTXSTATIC_H__

#define DmtxAlmostZero          0.000001
#define DmtxAlmostInfinity            -1

#define DmtxValueC40Latch            230
#define DmtxValueTextLatch           239
#define DmtxValueX12Latch            238
#define DmtxValueEdifactLatch        240
#define DmtxValueBase256Latch        231

#define DmtxValueCTXUnlatch   254
#define DmtxValueEdifactUnlatch       31

#define DmtxValueAsciiPad            129
#define DmtxValueAsciiUpperShift     235
#define DmtxValueCTXShift1      0
#define DmtxValueCTXShift2      1
#define DmtxValueCTXShift3      2
#define DmtxValueFNC1                232
#define DmtxValueStructuredAppend    233
#define DmtxValue05Macro             236
#define DmtxValue06Macro             237
#define DmtxValueECI                 241

#define DmtxC40TextBasicSet            0
#define DmtxC40TextShift1              1
#define DmtxC40TextShift2              2
#define DmtxC40TextShift3              3

#define DmtxUnlatchExplicit            0
#define DmtxUnlatchImplicit            1

#define DmtxChannelValid            0x00
#define DmtxChannelUnsupportedChar  0x01 << 0
#define DmtxChannelCannotUnlatch    0x01 << 1

#undef min
#define min(X,Y) (((X) < (Y)) ? (X) : (Y))

#undef max
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

typedef enum {
   DmtxEncodeNormal,  /* Use normal scheme behavior (e.g., ASCII auto) */
   DmtxEncodeCompact, /* Use only compact format within scheme */
   DmtxEncodeFull     /* Use only fully expanded format within scheme */
} DmtxEncodeOption;

typedef enum {
   DmtxRangeGood,
   DmtxRangeBad,
   DmtxRangeEnd
} DmtxRange;

typedef enum {
   DmtxEdgeTop               = 0x01 << 0,
   DmtxEdgeBottom            = 0x01 << 1,
   DmtxEdgeLeft              = 0x01 << 2,
   DmtxEdgeRight             = 0x01 << 3
} DmtxEdge;

typedef enum {
   DmtxMaskBit8              = 0x01 << 0,
   DmtxMaskBit7              = 0x01 << 1,
   DmtxMaskBit6              = 0x01 << 2,
   DmtxMaskBit5              = 0x01 << 3,
   DmtxMaskBit4              = 0x01 << 4,
   DmtxMaskBit3              = 0x01 << 5,
   DmtxMaskBit2              = 0x01 << 6,
   DmtxMaskBit1              = 0x01 << 7
} DmtxMaskBit;

/**
 * @struct DmtxFollow
 * @brief DmtxFollow
 */
typedef struct DmtxFollow_struct {
   unsigned char  *ptr;
   unsigned char   neighbor;
   int             step;
   DmtxPixelLoc    loc;
} DmtxFollow;

/**
 * @struct DmtxBresLine
 * @brief DmtxBresLine
 */
typedef struct DmtxBresLine_struct {
   int             xStep;
   int             yStep;
   int             xDelta;
   int             yDelta;
   int             steep;
   int             xOut;
   int             yOut;
   int             travel;
   int             outward;
   int             error;
   DmtxPixelLoc    loc;
   DmtxPixelLoc    loc0;
   DmtxPixelLoc    loc1;
} DmtxBresLine;

typedef struct C40TextState_struct {
   int             shift;
   DmtxBoolean     upperShift;
} C40TextState;

/* dmtxregion.c */
double RightAngleTrueness(DmtxVector2 c0, DmtxVector2 c1, DmtxVector2 c2, double angle);
DmtxPointFlow MatrixRegionSeekEdge(DmtxDecode *dec, DmtxPixelLoc loc0);
DmtxPassFail MatrixRegionOrientation(DmtxDecode *dec, DmtxRegion *reg, DmtxPointFlow flowBegin);
long DistanceSquared(DmtxPixelLoc a, DmtxPixelLoc b);
int ReadModuleColor(DmtxDecode *dec, DmtxRegion *reg, int symbolRow, int symbolCol, int sizeIdx, int colorPlane);

DmtxPassFail MatrixRegionFindSize(DmtxDecode *dec, DmtxRegion *reg);
int CountJumpTally(DmtxDecode *dec, DmtxRegion *reg, int xStart, int yStart, DmtxDirection dir);
DmtxPointFlow GetPointFlow(DmtxDecode *dec, int colorPlane, DmtxPixelLoc loc, int arrive);
DmtxPointFlow FindStrongestNeighbor(DmtxDecode *dec, DmtxPointFlow center, int sign);
DmtxFollow FollowSeek(DmtxDecode *dec, DmtxRegion *reg, int seek);
DmtxFollow FollowSeekLoc(DmtxDecode *dec, DmtxPixelLoc loc);
DmtxFollow FollowStep(DmtxDecode *dec, DmtxRegion *reg, DmtxFollow followBeg, int sign);
DmtxFollow FollowStep2(DmtxDecode *dec, DmtxFollow followBeg, int sign);
DmtxPassFail TrailBlazeContinuous(DmtxDecode *dec, DmtxRegion *reg, DmtxPointFlow flowBegin, int maxDiagonal);
int TrailBlazeGapped(DmtxDecode *dec, DmtxRegion *reg, DmtxBresLine line, int streamDir);
int TrailClear(DmtxDecode *dec, DmtxRegion *reg, int clearMask);
DmtxBestLine FindBestSolidLine(DmtxDecode *dec, DmtxRegion *reg, int step0, int step1, int streamDir, int houghAvoid);
DmtxBestLine FindBestSolidLine2(DmtxDecode *dec, DmtxPixelLoc loc0, int tripSteps, int sign, int houghAvoid);
DmtxPassFail FindTravelLimits(DmtxDecode *dec, DmtxRegion *reg, DmtxBestLine *line);
DmtxPassFail MatrixRegionAlignCalibEdge(DmtxDecode *dec, DmtxRegion *reg, int whichEdge);
DmtxBresLine BresLineInit(DmtxPixelLoc loc0, DmtxPixelLoc loc1, DmtxPixelLoc locInside);
DmtxPassFail BresLineGetStep(DmtxBresLine line, DmtxPixelLoc target, int *travel, int *outward);
DmtxPassFail BresLineStep(DmtxBresLine *line, int travel, int outward);
/*static void WriteDiagnosticImage(DmtxDecode *dec, DmtxRegion *reg, char *imagePath);*/

/* dmtxdecode.c */
void TallyModuleJumps(DmtxDecode *dec, DmtxRegion *reg, int tally[][24], int xOrigin, int yOrigin, int mapWidth, int mapHeight, DmtxDirection dir);
DmtxPassFail PopulateArrayFromMatrix(DmtxDecode *dec, DmtxRegion *reg, DmtxMessage *msg);

/* dmtxdecodescheme.c */
void DecodeDataStream(DmtxMessage *msg, int sizeIdx, unsigned char *outputStart);
int GetEncodationScheme(unsigned char cw);
void PushOutputWord(DmtxMessage *msg, int value);
void PushOutputC40TextWord(DmtxMessage *msg, C40TextState *state, int value);
void PushOutputMacroHeader(DmtxMessage *msg, int macroType);
void PushOutputMacroTrailer(DmtxMessage *msg);
unsigned char *DecodeSchemeAscii(DmtxMessage *msg, unsigned char *ptr, unsigned char *dataEnd);
unsigned char *DecodeSchemeC40Text(DmtxMessage *msg, unsigned char *ptr, unsigned char *dataEnd, DmtxScheme encScheme);
unsigned char *DecodeSchemeX12(DmtxMessage *msg, unsigned char *ptr, unsigned char *dataEnd);
unsigned char *DecodeSchemeEdifact(DmtxMessage *msg, unsigned char *ptr, unsigned char *dataEnd);
unsigned char *DecodeSchemeBase256(DmtxMessage *msg, unsigned char *ptr, unsigned char *dataEnd);

/* dmtxencode.c */
void PrintPattern(DmtxEncode *encode);
int EncodeDataCodewords(DmtxByteList *input, DmtxByteList *output, int sizeIdxRequest, DmtxScheme scheme);

/* dmtxplacemod.c */
int ModulePlacementEcc200(unsigned char *modules, unsigned char *codewords, int sizeIdx, int moduleOnColor);
void PatternShapeStandard(unsigned char *modules, int mappingRows, int mappingCols, int row, int col, unsigned char *codeword, int moduleOnColor);
void PatternShapeSpecial1(unsigned char *modules, int mappingRows, int mappingCols, unsigned char *codeword, int moduleOnColor);
void PatternShapeSpecial2(unsigned char *modules, int mappingRows, int mappingCols, unsigned char *codeword, int moduleOnColor);
void PatternShapeSpecial3(unsigned char *modules, int mappingRows, int mappingCols, unsigned char *codeword, int moduleOnColor);
void PatternShapeSpecial4(unsigned char *modules, int mappingRows, int mappingCols, unsigned char *codeword, int moduleOnColor);
void PlaceModule(unsigned char *modules, int mappingRows, int mappingCols, int row, int col,
      unsigned char *codeword, int mask, int moduleOnColor);

/* dmtxreedsol.c */
DmtxPassFail RsEncode(DmtxMessage *message, int sizeIdx);
DmtxPassFail RsDecode(unsigned char *code, int sizeIdx, int fix);
DmtxPassFail RsGenPoly(DmtxByteList *gen, int errorWordCount);
DmtxBoolean RsComputeSyndromes(DmtxByteList *syn, const DmtxByteList *rec, int blockErrorWords);
DmtxBoolean RsFindErrorLocatorPoly(DmtxByteList *elp, const DmtxByteList *syn, int errorWordCount, int maxCorrectable);
DmtxBoolean RsFindErrorLocations(DmtxByteList *loc, const DmtxByteList *elp);
DmtxPassFail RsRepairErrors(DmtxByteList *rec, const DmtxByteList *loc, const DmtxByteList *elp, const DmtxByteList *syn);

/* dmtxscangrid.c */
DmtxScanGrid InitScanGrid(DmtxDecode *dec);
int PopGridLocation(DmtxScanGrid *grid, /*@out@*/ DmtxPixelLoc *locPtr);
int GetGridCoordinates(DmtxScanGrid *grid, /*@out@*/ DmtxPixelLoc *locPtr);
void SetDerivedFields(DmtxScanGrid *grid);

/* dmtxsymbol.c */
int FindSymbolSize(int dataWords, int sizeIdxRequest);

/* dmtximage.c */
int GetBitsPerPixel(int pack);

/* dmtxencodestream.c */
DmtxEncodeStream StreamInit(DmtxByteList *input, DmtxByteList *output);
void StreamCopy(DmtxEncodeStream *dst, DmtxEncodeStream *src);
void StreamMarkComplete(DmtxEncodeStream *stream, int sizeIdx);
void StreamMarkInvalid(DmtxEncodeStream *stream, int reasonIdx);
void StreamMarkFatal(DmtxEncodeStream *stream, int reasonIdx);
void StreamOutputChainAppend(DmtxEncodeStream *stream, DmtxByte value);
DmtxByte StreamOutputChainRemoveLast(DmtxEncodeStream *stream);
void StreamOutputSet(DmtxEncodeStream *stream, int index, DmtxByte value);
DmtxBoolean StreamInputHasNext(DmtxEncodeStream *stream);
DmtxByte StreamInputPeekNext(DmtxEncodeStream *stream);
DmtxByte StreamInputAdvanceNext(DmtxEncodeStream *stream);
void StreamInputAdvancePrev(DmtxEncodeStream *stream);

/* dmtxencodescheme.c */
int EncodeSingleScheme(DmtxByteList *input, DmtxByteList *output, int sizeIdxRequest, DmtxScheme scheme);
void EncodeNextChunk(DmtxEncodeStream *stream, int scheme, int subScheme, int sizeIdxRequest);
void EncodeChangeScheme(DmtxEncodeStream *stream, DmtxScheme targetScheme, int unlatchType);
int GetRemainingSymbolCapacity(int outputLength, int sizeIdx);

/* dmtxencodeoptimize.c */
int EncodeOptimizeBest(DmtxByteList *input, DmtxByteList *output, int sizeIdxRequest);
void StreamAdvanceFromBest(DmtxEncodeStream *streamNext,
      DmtxEncodeStream *streamList, int targeteState, int sizeIdxRequest);
void AdvanceAsciiCompact(DmtxEncodeStream *streamNext, DmtxEncodeStream *streamList,
      int state, int inputNext, int sizeIdxRequest);
void AdvanceCTX(DmtxEncodeStream *streamNext, DmtxEncodeStream *streamList,
      int state, int inputNext, int ctxValueCount, int sizeIdxRequest);
void AdvanceEdifact(DmtxEncodeStream *streamNext, DmtxEncodeStream *streamList,
      int state, int inputNext, int sizeIdxRequest);
int GetScheme(int state);
DmtxBoolean ValidStateSwitch(int fromState, int targetState);

/* dmtxencodeascii.c */
void EncodeNextChunkAscii(DmtxEncodeStream *stream, int option);
void AppendValueAscii(DmtxEncodeStream *stream, DmtxByte value);
void CompleteIfDoneAscii(DmtxEncodeStream *stream, int sizeIdxRequest);
void PadRemainingInAscii(DmtxEncodeStream *stream, int sizeIdx);
DmtxByteList EncodeTmpRemainingInAscii(DmtxEncodeStream *stream, DmtxByte *storage, int capacity, DmtxPassFail *passFail);
DmtxByte Randomize253State(DmtxByte cwValue, int cwPosition);

/* dmtxencodec40textx12.c */
void EncodeNextChunkCTX(DmtxEncodeStream *stream, int sizeIdxRequest);
void AppendValuesCTX(DmtxEncodeStream *stream, DmtxByteList *valueList);
void AppendUnlatchCTX(DmtxEncodeStream *stream);
void CompleteIfDoneCTX(DmtxEncodeStream *stream, int sizeIdxRequest);
void CompletePartialC40Text(DmtxEncodeStream *stream, DmtxByteList *valueList, int sizeIdxRequest);
void CompletePartialX12(DmtxEncodeStream *stream, DmtxByteList *valueList, int sizeIdxRequest);
DmtxBoolean PartialX12ChunkRemains(DmtxEncodeStream *stream);
void PushCTXValues(DmtxByteList *valueList, DmtxByte inputValue, int targetScheme, DmtxPassFail *passFail);
DmtxBoolean IsCTX(int scheme);
void ShiftValueListBy3(DmtxByteList *list, DmtxPassFail *passFail);

/* dmtxencodeedifact.c */
void EncodeNextChunkEdifact(DmtxEncodeStream *stream);
void AppendValueEdifact(DmtxEncodeStream *stream, DmtxByte value);
void CompleteIfDoneEdifact(DmtxEncodeStream *stream, int sizeIdxRequest);

/* dmtxencodebase256.c */
void EncodeNextChunkBase256(DmtxEncodeStream *stream);
void AppendValueBase256(DmtxEncodeStream *stream, DmtxByte value);
void CompleteIfDoneBase256(DmtxEncodeStream *stream, int sizeIdxRequest);
void UpdateBase256ChainHeader(DmtxEncodeStream *stream, int perfectSizeIdx);
void Base256OutputChainInsertFirst(DmtxEncodeStream *stream);
void Base256OutputChainRemoveFirst(DmtxEncodeStream *stream);
DmtxByte Randomize255State(DmtxByte cwValue, int cwPosition);
unsigned char UnRandomize255State(unsigned char value, int idx);

static const int dmtxNeighborNone = 8;
static const int dmtxPatternX[] = { -1,  0,  1,  1,  1,  0, -1, -1 };
static const int dmtxPatternY[] = { -1, -1, -1,  0,  1,  1,  1,  0 };
static const DmtxPointFlow dmtxBlankEdge = { 0, 0, 0, DmtxUndefined, { -1, -1 } };

/*@ +charint @*/

static int rHvX[] =
    {  256,  256,  256,  256,  255,  255,  255,  254,  254,  253,  252,  251,  250,  249,  248,
       247,  246,  245,  243,  242,  241,  239,  237,  236,  234,  232,  230,  228,  226,  224,
       222,  219,  217,  215,  212,  210,  207,  204,  202,  199,  196,  193,  190,  187,  184,
       181,  178,  175,  171,  168,  165,  161,  158,  154,  150,  147,  143,  139,  136,  132,
       128,  124,  120,  116,  112,  108,  104,  100,   96,   92,   88,   83,   79,   75,   71,
        66,   62,   58,   53,   49,   44,   40,   36,   31,   27,   22,   18,   13,    9,    4,
         0,   -4,   -9,  -13,  -18,  -22,  -27,  -31,  -36,  -40,  -44,  -49,  -53,  -58,  -62,
       -66,  -71,  -75,  -79,  -83,  -88,  -92,  -96, -100, -104, -108, -112, -116, -120, -124,
      -128, -132, -136, -139, -143, -147, -150, -154, -158, -161, -165, -168, -171, -175, -178,
      -181, -184, -187, -190, -193, -196, -199, -202, -204, -207, -210, -212, -215, -217, -219,
      -222, -224, -226, -228, -230, -232, -234, -236, -237, -239, -241, -242, -243, -245, -246,
      -247, -248, -249, -250, -251, -252, -253, -254, -254, -255, -255, -255, -256, -256, -256 };

static int rHvY[] =
    {    0,    4,    9,   13,   18,   22,   27,   31,   36,   40,   44,   49,   53,   58,   62,
        66,   71,   75,   79,   83,   88,   92,   96,  100,  104,  108,  112,  116,  120,  124,
       128,  132,  136,  139,  143,  147,  150,  154,  158,  161,  165,  168,  171,  175,  178,
       181,  184,  187,  190,  193,  196,  199,  202,  204,  207,  210,  212,  215,  217,  219,
       222,  224,  226,  228,  230,  232,  234,  236,  237,  239,  241,  242,  243,  245,  246,
       247,  248,  249,  250,  251,  252,  253,  254,  254,  255,  255,  255,  256,  256,  256,
       256,  256,  256,  256,  255,  255,  255,  254,  254,  253,  252,  251,  250,  249,  248,
       247,  246,  245,  243,  242,  241,  239,  237,  236,  234,  232,  230,  228,  226,  224,
       222,  219,  217,  215,  212,  210,  207,  204,  202,  199,  196,  193,  190,  187,  184,
       181,  178,  175,  171,  168,  165,  161,  158,  154,  150,  147,  143,  139,  136,  132,
       128,  124,  120,  116,  112,  108,  104,  100,   96,   92,   88,   83,   79,   75,   71,
        66,   62,   58,   53,   49,   44,   40,   36,   31,   27,   22,   18,   13,    9,    4 };

/*@ -charint @*/

enum DmtxErrorMessage {
   DmtxErrorUnknown,
   DmtxErrorUnsupportedCharacter,
   DmtxErrorNotOnByteBoundary,
   DmtxErrorIllegalParameterValue,
   DmtxErrorEmptyList,
   DmtxErrorOutOfBounds,
   DmtxErrorMessageTooLarge,
   DmtxErrorCantCompactNonDigits,
   DmtxErrorUnexpectedScheme,
   DmtxErrorIncompleteValueList
};

static char *dmtxErrorMessage[] = {
   "Unknown error",
   "Unsupported character",
   "Not on byte boundary",
   "Illegal parameter value",
   "Encountered empty list",
   "Out of bounds",
   "Message too large",
   "Can't compact non-digits",
   "Encountered unexpected scheme",
   "Encountered incomplete value list"
};

#endif
