unsigned char number_tobool  (avm_memcell* m)   {return m->data.numVal    != 0; }
unsigned char string_tobool  (avm_memcell* m)   {return m->data.strVal[0] != 0; }
unsigned char bool_tobool    (avm_memcell* m)   {return m->data.boolVal   != 0; }
unsigned char table_tobool   (avm_memcell* m)   {return 1;                      }
unsigned char userfunc_tobool(avm_memcell* m)   {return 1;                      }
unsigned char libfunc_tobool (avm_memcell* m)   {return 1;                      }
unsigned char nil_tobool     (avm_memcell* m)   {return 0;                      }
unsigned char undef_tobool   (avm_memcell* m)   {assert(0); return 0;           }

unsigned char avm_tobool(avm_memcell* m){
    assert(m->type>=0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

void execute_jeq (Instruction* instr){
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality!");
        executionFinished = 1;
    }else if(rv1->type == nil_m || rv2->type == nil_m){
        result = (rv1->type == nil_m && rv2->type == nil_m);
    }else if(rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }else if(rv1->type != rv2->type){
        char errorMessage[100];
        sprintf(errorMessage,"%s == %s is illegal!",
                    typeStrings[rv1->type],
                    typeStrings[rv2->type]  );
        avm_error(errorMessage);
    }else{
        switch(rv1->type){
            case 0: result = rv1->data.numVal == rv2->data.numVal; break;
            case 1: result = strcmp(rv1->data.strVal,rv2->data.strVal) == 0;   break;
            case 2: assert(0); break;
            case 3:
            case 4:
            case 5:
            case 6: assert(0); break;
            case 7: assert(0); break;
            default: assert(0); break;
        }
    }
    if(!executionFinished && result){
        pc = instr->result->val;
    }
}

void execute_jne (Instruction* instr){
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in ineguity!");
        executionFinished = 1;
    }else if(rv1->type == nil_m || rv2->type == nil_m){
        result = !(rv1->type == nil_m && rv2->type == nil_m);
    }else if(rv1->type == bool_m || rv2->type == bool_m){
        result = !(avm_tobool(rv1) == avm_tobool(rv2));
    }else if(rv1->type != rv2->type){
        char errorMessage[100];
        sprintf(errorMessage,"%s != %s is illegal!",
                    typeStrings[rv1->type],
                    typeStrings[rv2->type]  );
        avm_error(errorMessage);
    }else{
        switch(rv1->type){
            case 0: result = rv1->data.numVal != rv2->data.numVal; break;
            case 1: result = strcmp(rv1->data.strVal,rv2->data.strVal) != 0; break;
            case 2: assert(0); break;
            case 3:
            case 4:
            case 5:
            case 6: assert(0); break;
            case 7: assert(0); break;
            default: assert(0); break;
        }
    }

    if(!executionFinished && result){
        pc = instr->result->val;
    }
}
void execute_jle (Instruction* instr) {
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == number_m && rv2->type == number_m){
        result = rv1->data.numVal <= rv2->data.numVal;
    }else if(rv1->type == string_m && rv2->type == string_m){
        result = strcmp(rv1->data.strVal,rv2->data.strVal) <= 0;
    }else{
        avm_error("argument is not number!");
        executionFinished = 1;
    }

    if(!executionFinished && result){
        pc = instr->result->val;
    }
}
void execute_jge (Instruction* instr) {
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == number_m && rv2->type == number_m){
        result = rv1->data.numVal >= rv2->data.numVal;
    }else if(rv1->type == string_m && rv2->type == string_m){
        result = strcmp(rv1->data.strVal,rv2->data.strVal) >= 0;
    }else{
        avm_error("argument is not number!");
        executionFinished = 1;
    }

    if(!executionFinished && result){
        pc = instr->result->val;
    }
}
void execute_jlt (Instruction* instr) {
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == number_m && rv2->type == number_m){
        result = rv1->data.numVal < rv2->data.numVal;
    }else if(rv1->type == string_m && rv2->type == string_m){
        result = strcmp(rv1->data.strVal,rv2->data.strVal) < 0;
    }else{
        avm_error("argument is not number!");
        executionFinished = 1;
    }

    if(!executionFinished && result){
        pc = instr->result->val;
    }
}
void execute_jgt (Instruction* instr) {
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == number_m && rv2->type == number_m){
        result = rv1->data.numVal > rv2->data.numVal;
    }else if(rv1->type == string_m && rv2->type == string_m){
        result = strcmp(rv1->data.strVal,rv2->data.strVal) > 0;
    }else{
        avm_error("argument is not number!");
        executionFinished = 1;
    }

    if(!executionFinished && result){
        pc = instr->result->val;
    }
}
void execute_jump (Instruction *instr){
    pc = instr->result->val;
}
void execute_or (Instruction* instr){assert(0);}
void execute_and (Instruction* instr){assert(0);}
void execute_not (Instruction* instr){assert(0);}
void execute_uminus (Instruction* instr){assert(0);}

