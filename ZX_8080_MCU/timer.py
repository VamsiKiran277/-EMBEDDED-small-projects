if request.IsRead:
    if request.Offset == 0x0C:
        # When C code reads TIM_STAT, return 1 to trigger the toggle
        request.Value = 0x1
