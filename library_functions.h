void libfunc_objectmemberkeys(void){}
void libfunc_objecttotalmember(void){}
void libfunc_objectcopy(void){}
void libfunc_argument(void){}
void libfunc_strtonum(void){}



void libfunc_input(){
    unsigned n = avm_totalactuals();
    char* s = (char*)malloc(1000*sizeof(char));
    if(n!=0){
        char errorMessage[100];
        sprintf(errorMessage , "0 argument (not %d) expected in 'input'",n);
        avm_error(errorMessage);
    }else{
        avm_memcellclear(&retval);
        scanf("%s",s);
        for(int j=0; s[j]!='\0'; j++){
            if(!isdigit(s[j]) && s[j] != '.'){
                retval.type = string_m;
                retval.data.strVal = strdup(s);
                return;
            }
        }
        double temp;
        sscanf(s,"%lf",&temp);
        retval.type = number_m;
        retval.data.numVal = temp;
    }
}
double Power(double* data){
    if(data == NULL) return 0;
    if(*data == 0) return 0;
    if(data[1] == 0) return data[0];
    double mul = 1;
    for(int i=0; i< data[1]; i++){
        mul = mul * data[0];
    }
    data[1] = mul;
    return Power(&data[1]);
}
void libfunc_sqrt(){
    unsigned n = avm_totalactuals();
    unsigned i = 0;
    double data;
    if(n != 1){
        avm_error("more arguments needed in sqrt!");
    }else{
        char* s = avm_tostring(avm_getactual(i));
        for(int j=0; s[j]!='\0'; j++){
            if(!isdigit(s[j]) && s[j] != '.'){
                char errorMessage[100];
                sprintf(errorMessage,"argument %d in sqrt is not number!",i);
                avm_error(errorMessage);
            }
        }
        sscanf(s,"%lf", &data);
        avm_memcellclear(&retval);
        retval.data.numVal = sqrt(data);
        retval.type = number_m;
    }
}
void libfunc_print(void){
    unsigned n = avm_totalactuals();
    unsigned i = 0;
    char* data;
    for(i = 0; i < n; i++){
        char* s = avm_tostring(avm_getactual(i));
        data = strdup(s);
        printf("%s" , data);
        free(data);
    }
}
void libfunc_cos(void){
    unsigned n = avm_totalactuals();
    unsigned i = 0;
    double data;
    if(n!=1){
        avm_error("1 argument must be in cos!");
    }else{
        char* s = avm_tostring(avm_getactual(i));
        for(int j=0; s[j]!='\0'; j++){
            if(!isdigit(s[j]) && s[j] != '.'){
                char errorMessage[100];
                sprintf(errorMessage,"argument %d in sqrt is not number!",i);
                avm_error(errorMessage);
            }
        }
        sscanf(s,"%lf", &data);
        avm_memcellclear(&retval);
        retval.data.numVal = cos(data);
        retval.type = number_m;
    }
}
void libfunc_sin(void){
    unsigned n = avm_totalactuals();
    unsigned i = 0;
    double data;
    if(n!=1){
        avm_error("1 argument must be in sin!");
    }else{
        char* s = avm_tostring(avm_getactual(i));
        for(int j=0; s[j]!='\0'; j++){
            if(!isdigit(s[j]) && s[j] != '.'){
                char errorMessage[100];
                sprintf(errorMessage,"argument %d in sqrt is not number!",i);
                avm_error(errorMessage);
            }
        }
        sscanf(s,"%lf", &data);
        avm_memcellclear(&retval);
        retval.data.numVal = sin(data);
        retval.type = number_m;
    }
}
void libfunc_typeof(){
    unsigned n = avm_totalactuals();
    if(n!=1){
        char errorMessage[100];
        sprintf(errorMessage , "one argument (not %d) expected in 'typeof'",n);
        avm_error(errorMessage);
    }else{
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}
void libfunc_totalarguments(){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp){
        avm_error("'totalarguments' called outside a function");
        retval.type = nil_m;
    }else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_SAVEDTOPSP_OFFSET);
    }
}