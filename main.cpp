#include "./util.hpp"

using namespace cc;

float potential_gamma(float theta) {
    if (!theta) throw std::runtime_error("failed to calculate potential_gamma");
    return 13.0f * theta - 10.0f * std::log(theta);
}

float potential_gamma_delta(float theta) {
    if (!theta) throw std::runtime_error("failed to calculate potential_gamma_delta");
    return 13.0f - (10.0f / theta);
}

float hamiltonian_gamma(float theta, float p) {
    return potential_gamma(theta) + p * p / 2;
}

int main(int argc, char *argv[]) {
    try {
        const float step   = 0.01f;
        const int   n_leap = 10;
        const int   n_loop = 1000000;
        const int   n_burn = n_loop / 10;

        // ハミルトニアンモンテカルロで事後分布がガンマ分布である場合の乱数を得る
        vec_t vt;
        vec_t vp;
        int   accept = 0;
        float curr_t = 1.0f;
        for (int i = 0; i < n_loop; i++) {
            // 独立な標準正規乱数を発生させる
            float curr_p = gaussian_rand(0.0f, 1.0f);

            // リープフロッグ法で遷移させる
			vec_t trail_t;
			vec_t trail_p;
            float next_t = curr_t;
            float next_p = curr_p;
            for (int l = 0; l < n_leap; l++) {
                float halfway = next_p  - step * potential_gamma_delta(next_t) / 2;
                next_t = next_t  + step * halfway;
                next_p = halfway - step * potential_gamma_delta(next_t) / 2;
                trail_t.push_back(next_t);
                trail_p.push_back(next_p);
            }

            // 位相空間での軌跡をプロットする
            // std::ofstream ofs("output");
            // for (int l = 0; l < n_leap; l++) {
            //     ofs << format_str("%f %f %f", trail_t[l], trail_p[l], hamiltonian_gamma(trail_t[l], trail_p[l])) << std::endl;
            // }
            // exit(0);

            float curr_h = hamiltonian_gamma(curr_t, curr_p);
            float next_h = hamiltonian_gamma(next_t, next_p);
            float r      = std::exp(curr_h - next_h);

            if (std::min(1.0f, r) > uniform_rand(0.0f, 1.0f)) {
                accept++;
                curr_t = next_t;
                curr_p = next_p;
            }
            vp.push_back(curr_p);
            vt.push_back(curr_t);
        }

        // 受容率を調べる
        std::cout << format_str("persec: %.3f%%", 100.0f * accept / n_loop) << std::endl;

        // バーンイン期間を破棄する
        std::rotate(vt.begin(), vt.begin() + n_burn, vt.end());
        vt.resize(vt.size() - n_burn);

        // EAP推定値を求める
        std::cout << format_str("mean: %f", std::accumulate(vt.begin(), vt.end(), 0.0f) / vt.size()) << std::endl;

        // ストリップ毎に頻度を計算する
        const float strip = 0.1f;
        const int   range = 30;
        vec_t       frequency(range);
        for (auto v : vt) {
            int pos = (int)(v / strip);
            if (pos >= 0 && pos < range) {
                frequency[pos] += v;
            }
        }

        // 相対度数でプロットする
        std::ofstream ofs("output");
        for (size_t i = 0; i < frequency.size(); i++) {
            float x = i * strip;
            float y = frequency[i] / (strip * std::accumulate(frequency.begin(), frequency.end(), 0.0f));
            ofs << format_str("%f %f", x, y) << std::endl;
        }

        // // 平均170、分散49の正規分布から1000個の標本を作る
        // vec_t samples;
        // for (int i = 0; i < 1000; i++) {
        //     samples.push_back(gaussian_rand(170.0f, std::sqrt(49.0f)));
        // }
        //
        // // 標本平均と標本分散を求める
        // float sm = std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
        // float sv = 0.0f;
        // for (auto v : samples) {
        //     sv += std::pow(v - sm, 2.0f) / samples.size();
        // }
    } catch (const std::exception &e) {
        std::cerr << colorant('y', format_str("error: %s", e.what())) << std::endl;
    }
}

