
void avm_tablebucketsinit(avm_table_bucket** p){
    p = (avm_table_bucket**)malloc(AVM_TABLE_HASHSIZE*sizeof(avm_table_bucket*));
    for( unsigned i = 0; i<AVM_TABLE_HASHSIZE; i++){
        p[i] = NULL;
    }
}

avm_table_bucket* insertToBucket(avm_memcell* toInsert , avm_memcell* index , avm_table_bucket* toWhere){
        assert(index->type == number_m || index->type == string_m || index->type == libfunc_m || index->type == bool_m);
        avm_table_bucket* newlist = toWhere;
        avm_table_bucket* node = (avm_table_bucket*)calloc(1,sizeof(avm_table_bucket));

        if(toWhere == NULL){
            node->next = NULL;
            //node->key.type = undef_m;
            avm_assign(&(node->key) , index);
            //node->value.type = undef_m;
            avm_assign(&(node->value) , toInsert);
            return node;
        }
        while(newlist->next != NULL){
            if(index->type == number_m){
                if(newlist->key.data.numVal == index->data.numVal){
                    avm_assign(&(newlist->value), toInsert);
                    return toWhere;
                }
            }else if(index->type == string_m){
                if(strcmp(newlist->key.data.strVal, index->data.strVal) == 0){
                    avm_assign(&(newlist->value), toInsert);
                    return toWhere;
                }
            }else if(index->type == libfunc_m){
                if(strcmp(newlist->key.data.libfuncVal, index->data.libfuncVal) == 0){
                    avm_assign(&(newlist->value), toInsert);
                    return toWhere;
                }
            }else if(index->type == bool_m){
                    avm_assign(&(newlist->value), toInsert);
                    return toWhere;
            }
            newlist = newlist->next;
        }
        avm_assign(&(node->key) , index);
        avm_assign(&(node->value) , toInsert);
        node->next = toWhere;
        return node;
}


avm_table* avm_tablenew(void){
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter = 0;
    t->total = 0;
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->libIndexed);
    return t;
}

void avm_tabledestroy (avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}

void avm_tableincrefcounter(avm_table* t){  t->refCounter++;    }
void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter)    avm_tabledestroy(t);
}

void avm_tablebucketsdestroy(avm_table_bucket** p){
    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; i++,p++){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}

void execute_newtable (Instruction* instr){
    avm_memcell* lv = avm_translate_operand(instr->arg1, ((avm_memcell*)0));
    assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){
    assert(index->type == number_m || index->type == string_m || index->type == libfunc_m || index->type == bool_m);
    avm_memcell* content = (avm_memcell*)calloc(1,sizeof(avm_memcell));
    avm_table_bucket* temp;
    int hashCode;
    if(index->type == string_m){
        hashCode = hashCodeString(index->data.strVal);
        temp = table->strIndexed[hashCode];
        while(temp != NULL){
            if(strcmp(temp->key.data.strVal, index->data.strVal) == 0){
                avm_assign(content,&(temp->value));
                break;
            }   temp = temp->next;
        }
    }else if(index->type == number_m){
        hashCode = hashCodeNumber(index->data.numVal);
        temp = table->numIndexed[hashCode];
        while(temp != NULL){
            if(temp->key.data.numVal == index->data.numVal){
                avm_assign(content,&(temp->value));
                break;
            }   temp =temp->next;
        }
    }else if(index->type == libfunc_m){
        hashCode = hashCodeNumber(index->data.libfuncVal);
        temp = table->libIndexed[hashCode];
        while(temp != NULL){
            if(temp->key.data.libfuncVal == index->data.libfuncVal){
                avm_assign(content,&(temp->value));
                break;
            }   temp =temp->next;
        }
    }else if(index->type == bool_m){
        temp = table->boolIndexed[index->data.boolVal];
        avm_assign(content,&(temp->value));
    }
    return content;
}


void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content){

    assert(index->type == number_m || index->type == string_m || index->type == libfunc_m || index->type == bool_m);
    int hashedcode;

    if(index->type == string_m){
        hashedcode = hashCodeString(index->data.strVal);
        table->strIndexed[hashedcode] = insertToBucket(content , index , table->strIndexed[hashedcode]);
    }else if(index->type == number_m){
        hashedcode = hashCodeNumber(index->data.numVal);
        table->numIndexed[hashedcode] = insertToBucket(content , index , table->numIndexed[hashedcode]);
    }else if(index->type == libfunc_m){
        hashedcode = hashCodeNumber(index->data.libfuncVal);
        table->libIndexed[hashedcode] = insertToBucket(content , index , table->libIndexed[hashedcode]);
    }else if(index->type == bool_m){
        table->boolIndexed[index->data.boolVal] = insertToBucket(content , index , table->libIndexed[index->data.boolVal]);
    }
    return;
}

void execute_tablegetelem (Instruction* instr){
    avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* t  = avm_translate_operand(instr->arg1, (avm_memcell*) 0);
    avm_memcell* i  = avm_translate_operand(instr->arg2, &ax);

    assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
    assert(t && (&stack[N-1] >= t && t > &stack[top]));
    assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;
    if(t->type != table_m){
        char errorMessage[100];
        sprintf(errorMessage , "illigal use of type %s as table!",typeStrings[t->type]);
        avm_error(errorMessage);
    }else{
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if(content){
            avm_assign(lv, content);
        }else{
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            avm_warning("%s[%s] not found!",ts,is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem (Instruction* instr){
    avm_memcell* t = avm_translate_operand(instr->arg1, (avm_memcell*) 0);
    avm_memcell* i = avm_translate_operand(instr->arg2, &bx);
    avm_memcell* c = avm_translate_operand(instr->result, &ax);

    assert(t && (&stack[N-1] >= t && t > &stack[top]));
    assert(i && c);
    if(t->type != table_m){
        char errorMessage[100];
        sprintf(errorMessage , "illigal use of type %s as table!",typeStrings[t->type]);
        avm_error(errorMessage);      
    }else{
        avm_tablesetelem(t->data.tableVal, i ,c);
    }
}

void execute_nop (Instruction* instr){}