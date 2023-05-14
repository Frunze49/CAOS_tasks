void computation(float *a, int b, float *c) {
    float arr[] = {0., 0., 0., 0.};
    float tmp_arr[] = {0., 0., 0., 0.};
    float tmp = 0.;
    if (b != 0) {
        for (int i = 0; i < 4; ++i) {
            arr[i] = a[i];
        }
        b -= 4;
        a += 4;

        while (b != 0) {
            for (int i = 0; i < 4; ++i) {
                tmp_arr[i] = a[i];
                arr[i] *= tmp_arr[i];
            }
            b -= 4;
            a += 4;
        }
    }
    for (int i = 0; i < 4; ++i) {
        tmp += arr[i];
    }
    *c = tmp;
}