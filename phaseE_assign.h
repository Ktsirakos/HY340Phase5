void avm_warning(char* format,...){
    printf(BLUE"Warning: "RESET"%s\n",format);
}

void avm_assign (avm_memcell* lv , avm_memcell* rv){
    if( lv == rv) return;

    if(lv->type == table_m &&
       rv->type == table_m &&
       lv->data.tableVal == rv->data.tableVal) return;

    printf("PC: %d\t" , pc);
    if(rv->type == undef_m) {
        avm_warning("assigning from undef content!");
    }

    printf("\n");
    avm_memcellclear(lv);

    memcpy(lv , rv , sizeof(avm_memcell));
    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    }else if(lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_assign (Instruction* i){
    avm_memcell* lv = avm_translate_operand(i->result , (avm_memcell*) 0);
    avm_memcell* rv = avm_translate_operand(i->arg1 , &ax);

    assert(lv && &stack[N-1] >= lv && lv > &stack[top] || lv == &retval);
    assert(rv);
    
    avm_assign(lv , rv);

}