// Copyright 2023 Bulgakov Daniil

#include "../../../modules/task_1/bulgakov_d_slau_gradient/slau_gradient.h"

double vec_vec(const dvec &a, const dvec &b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

dvec matrix_vec(const dmat &a, const dvec b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] =  vec_vec(a[i], b);
    }
    return res;
}

dvec vec_vec_comb(double ma, const dvec& a, double mb, const dvec& b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] = ma * a[i] + mb * b[i];
    }
    return res;
}

double vec_norm(const dvec& a) {
    return sqrt(vec_vec(a, a));
}


dvec solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    int k = 0;

    while (k++ < a.size()) {
        dvec r_prev;
        dvec mv = matrix_vec(a, p);
        r_prev = r;

        double d = vec_vec(r, r) / std::max(vec_vec(p, mv), SMOL);
        res = vec_vec_comb(1.0, res, d, p);
        r = vec_vec_comb(1.0, r, -d, mv);

        if (vec_norm(r) < SMOL) break;

        double s = vec_vec(r, r) / std::max(vec_vec(r_prev, r_prev), SMOL);
        p = vec_vec_comb(1.0, r, s, p);
    }
    return res;
}
