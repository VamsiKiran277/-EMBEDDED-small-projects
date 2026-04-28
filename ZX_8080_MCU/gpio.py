if request.IsRead:
    if request.Offset == 0x10:
        # When C code reads START_CONV, return 0 so the while loop finishes
        request.Value = 0x0
    elif request.Offset == 0x14:
        # When C code reads ADC_VAL, return 3532 (0xDCC)
        request.Value = 0xDCC
