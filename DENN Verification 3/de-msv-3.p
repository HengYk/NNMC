</
    define p: main_original_res > 0.9;
    define q: main_optional_1000_res > 0.9;
    define r: main_original_res < main_optional_1000_res;
    alw (!(p and q) or r)
/>