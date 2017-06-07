void execute_call (Instruction* i){

    avm_memcell* func = avm_translate_operand(i->arg1 , &ax);
    assert(func);


    if(func->type == table_m){
        //printf("Calling function with table\n");
        FunctorCall(func->data.tableVal);
        return;
    }

    avm_callsaveenviroment();

    switch(func->type){

        case userfunc_m: {
            pc = userFuncs[func->data.funcVal].address;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
        }

        case string_m: {
            avm_calllibfunc(func->data.strVal);
            break;
        }
        case libfunc_m: {
            avm_calllibfunc(func->data.libfuncVal);
            break;
        }

        default: {
            char* s = avm_tostring(func);
            char errorMessage[100];
            sprintf(errorMessage , "Call: cannot bind %s to function!\n" , s);
            avm_error(errorMessage);
            free(s);
            executionFinished = 1;
        }
    }

}

void avm_dec_top(void){
    if(!top) {
        avm_error("Stack overflow");
        executionFinished = 1;
    }
    else {
        --top;
    }
}

void avm_push_envvalue(unsigned val){
    stack[top].type   = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenviroment(void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

userfunc* avm_getfuncinfo(unsigned address){
    userfunc* temp = userFuncs;
    for(int i=0; i<totalUserFuncs; i++){
        if(address == temp[i].address)
            return &temp[i];
    }
}

void execute_funcenter (Instruction* i){
    avm_memcell* func = avm_translate_operand(i->result , &ax);
    assert(func);
    assert(pc == userFuncs[func->data.funcVal].address);

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;

}

unsigned avm_get_envvalue(unsigned i){
    assert(stack[i].type == number_m);
    unsigned val = (unsigned) stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(Instruction* unused){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top) {
        avm_memcellclear(&stack[oldTop]);
    }
}
library_func_t avm_getlibraryfunc(char* id){
    if(strcmp(id,"print")==0){
        return libraryFuncs[0];
    }else if(strcmp(id,"input")==0){
        return libraryFuncs[1];
    }else if(strcmp(id,"objectmemberkeys")==0){
        return libraryFuncs[2];
    }else if(strcmp(id,"objecttotalmember")==0){
        return libraryFuncs[3];
    }else if(strcmp(id,"objectcopy")==0){
        return libraryFuncs[4];
    }else if(strcmp(id,"totalarguments")==0){
        return libraryFuncs[5];
    }else if(strcmp(id,"argument")==0){
        return libraryFuncs[6];
    }else if(strcmp(id,"typeof")==0){
        return libraryFuncs[7];
    }else if(strcmp(id,"strtonum")==0){
        return libraryFuncs[8];
    }else if(strcmp(id,"sqrt")==0){
        return libraryFuncs[9];
    }else if(strcmp(id,"cos")==0){
        return libraryFuncs[10];
    }else if(strcmp(id,"sin")==0){
        return libraryFuncs[11];
    }else{
        char errorMessage[100];
        sprintf(errorMessage , "unsupported lib func '%s' called!" , id);
        avm_error(errorMessage);
        executionFinished = 1;
        return 0;
    }
}

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);

    if(!f){
        char errorMessage[100];
        sprintf(errorMessage , "unsupported lib func '%s' called!" , id);
        avm_error(errorMessage);
        executionFinished = 1;
    }
    else
    {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished) execute_funcexit((Instruction*)0);
    }
}


unsigned avm_totalactuals(void){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
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
    double* data = (double*)malloc(n*sizeof(double));
    if(n<1){
        avm_error("0 arguments in sqrt!");
    }else{
        for(i = 0; i < n; i++){
            char* s = avm_tostring(avm_getactual(i));
            for(int j=0; s[j]!='\0'; j++){
                if(!isdigit(s[j]) && s[j] != '.'){
                    char errorMessage[100];
                    sprintf(errorMessage,"argument %d in sqrt is not number!",i);
                    avm_error(errorMessage);
                }
            }
            double temp;
            sscanf(s,"%lf", &temp);
            data[i] = temp;
        }
        Power(data);
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
    //printf("\n");
}

void libfunc_objectmemberkeys(void){}
void libfunc_objecttotalmember(void){}
void libfunc_objectcopy(void){}
void libfunc_argument(void){}
void libfunc_strtonum(void){}
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
//void avm_registrerlibfunc(char* id , library_func_t addr);


void execute_pusharg(Instruction* i){
    avm_memcell* arg = avm_translate_operand(i->arg1 , &ax);
    assert(arg);

    avm_assign(&stack[top] , arg);
    ++totalActuals;
    avm_dec_top();
}


void FunctorCall(avm_table* t){
    avm_memcell* functorCallIndex = malloc(sizeof(avm_memcell));
    functorCallIndex->type = string_m;
    functorCallIndex->data.strVal = strdup("()");

    avm_memcell* content = avm_tablegetelem(t , functorCallIndex);

    if(!content){
        printf("Tables doesn't include ()\n");
        return;
    }else{
        avm_callsaveenviroment();
        pc = userFuncs[content->data.funcVal].address;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
    }

        //if(content.type == userfunc_m)
        //else
            //if(content == table_m)
                //FunctorCall(content);
            //else printf("Error In functor Call with code 1\n");
        //else printf("Error in functor call with code 2\n");


}