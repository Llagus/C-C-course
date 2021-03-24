int *allocate_an_integer() {
    int i = 0;
    return &i;
}

int main() {
    int *j;
    j = allocate_an_integer();
    int k = *j;
    return 0;
}