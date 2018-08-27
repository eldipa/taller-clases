int sum(int* values, int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result += values[i];
    }
    return result;
}
