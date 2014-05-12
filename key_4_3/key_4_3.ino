const int num_rows=4;
const int num_cols=3;
const int debounce_time=20;

const char keymap[num_rows][num_cols]={
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
};

const int row_pins[num_rows]={7,6,5,4};
const int col_pins[num_cols]={11,10,9};


void setup(){
	Serial.begin(9600);
	for(int i=0; i< num_rows; i++)
	{
		pinMode(row_pins[i],INPUT);	
		digitalWrite(row_pins[i],HIGH);
	}

	for(int j=0; j< num_cols; j++)
	{
		pinMode(col_pins[j],OUTPUT);	
		digitalWrite(col_pins[j],HIGH);
	}
}
void loop()
{
//char key=get_key((char(*)[3])keymap,col_pins,row_pins,num_rows,num_cols);	
	char key=get_key();	
	if(key!=0){
		Serial.print("key:");
		Serial.println(key);
	}
}

char get_key(){
//char get_key(char (*keymap)[3],const int *col_pins,const int *row_pins,int num_rows,int num_cols){
	char key_value=0;
	for(int cn=0; cn<num_cols; cn++){
		digitalWrite(col_pins[cn],LOW);
		for(int rn=0; rn<num_rows; rn++){
			if(digitalRead(row_pins[rn])==LOW){
				delay(debounce_time);
				if(digitalRead(row_pins[rn])==LOW){
					while(digitalRead(row_pins[rn])==LOW);
					key_value= *(*(keymap+rn)+cn);
				}
			}
		}
		digitalWrite(col_pins[cn],HIGH);
	}
	return key_value;
}

