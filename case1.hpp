namespace case1 {
float potential(vec_t &t, vec_t &samples) {
    if (t[1] <= 0) throw std::runtime_error("failed to calculate potential");
    float sum_l2 = 0.0f;
    for (auto v : samples) {
        sum_l2 += std::pow(v - t[0], 2);
    }
    return (float)samples.size() * std::log(t[1]) / 2.0f + sum_l2 / t[1] / 2.0f;
}

vec_t potential_delta(vec_t &t, vec_t &samples) {
    if (t[1] <= 0) throw std::runtime_error("failed to calculate potential_delta");
    float sum_l1 = 0.0f;
    float sum_l2 = 0.0f;
    for (auto v : samples) {
        sum_l1 += v - t[0];
        sum_l2 += std::pow(v - t[0], 2);
    }
    vec_t ret {
        -sum_l1 / t[1],
        (float)samples.size() / 2.0f / t[1] - sum_l2 / 2.0f / t[1] / t[1]
    };
    return ret;
}

float hamiltonian(vec_t &t, vec_t &p, vec_t &samples) {
    return potential(t, samples) + (p[0] * p[0] + p[1] * p[1]) / 2.0f;
}

// ハミルトニアンモンテカルロでガウス分布のパラメタを推定する
void run() {
    const int dim    = 2;
    const int n_loop = 100000;
    const int n_burn = 90000;

    // 平均170、分散49の正規分布から1000個の標本を作る
    vec_t samples;
    for (int i = 0; i < 1000; i++) {
        samples.push_back(gaussian_rand(170.0f, std::sqrt(49.0f)));
    }

    // 標本平均と標本分散を求める
    float sm = std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
    float sv = 0.0f;
    for (auto v : samples) {
        sv += std::pow(v - sm, 2.0f) / samples.size();
    }

    vec_t curr_t {
        160.0f,
        30.0f
    };
    std::vector<vec_t> vt;
    for (int i = 0; i < n_loop; i++) {
        const float step   = 0.01f;
        const int   n_leap = 100;

        // 独立な標準正規乱数を発生させる
        vec_t curr_p {
            gaussian_rand(0.0f, 1.0f),
            gaussian_rand(0.0f, 1.0f)
        };

        // リープフロッグ法で遷移させる
        vec_t half_p(dim);
        vec_t next_t = curr_t;
        vec_t next_p = curr_p;
        for (int l = 0; l < n_leap; l++) {
            for (int i = 0; i < dim; i++) {
                half_p[i] = next_p[i] - step * potential_delta(next_t, samples)[i] / 2;
            }

            for (int i = 0; i < dim; i++) {
                next_t[i] += step * half_p[i];
            }

            for (int i = 0; i < dim; i++) {
                next_p[i] = half_p[i] - step * potential_delta(next_t, samples)[i] / 2;
            }
        }

        float curr_h = hamiltonian(curr_t, curr_p, samples);
        float next_h = hamiltonian(next_t, next_p, samples);
        float r      = std::exp(curr_h - next_h);
        if (std::min(1.0f, r) > uniform_rand(0.0f, 1.0f)) {
            curr_t = next_t;
        }
        vt.push_back(curr_t);
    }

    // バーンイン期間を破棄する
    std::rotate(vt.begin(), vt.begin() + n_burn, vt.end());
    vt.resize(vt.size() - n_burn);

    // EAP推定値を求める
    float mean = 0.0f;
    float var  = 0.0f;
    for (auto v : vt) {
        mean += v[0] / vt.size();
        var  += v[1] / vt.size();
    }
    std::cout << format_str("mean: %f", mean) << std::endl;
    std::cout << format_str("var: %f", var)   << std::endl;

    // プロットする
    std::ofstream ofs("output");
    for (auto v : vt) {
        ofs << format_str("%f %f", v[0], v[1]) << std::endl;
    }
}
}
