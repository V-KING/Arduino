#ifndef IR_RESULTS_H
#define IR_RESULTS_H
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
ir_results *ir_result;

#endif

