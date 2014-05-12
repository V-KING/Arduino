#ifndef IR_IRRESULTS_H
#define IR_IRRESULTS_H
#include <IRremote.h>
class ir_results
{
  public:
	decode_results results;
	unsigned int rawCodes[RAWBUF] ; // 不可识别的时候就存储ontime和offtime
	unsigned long codeValue;
	int codeLen;
	int codeType;
	int toggle;

};
ir_results ir_result;
#define codeType 			ir_result.codeType
#define codeValue 			ir_result.codeValue
#define	codeLen 			ir_result.codeLen
#define toggle 				ir_result.toggle


#endif
