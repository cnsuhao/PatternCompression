__kernel void computeScore(__global const char *combos, __global const int *stringSize, __global int *scores)
{
    const uint id = get_global_id(0);
    int score = 0;
    bool match = true;
    for(int i = 0; i < get_global_size(0); i++){
        if(combos[id] == combos[i] && id != i){
            for(int n = 1; n < stringSize[0]; n++){
                if(combos[id+n] != combos[i+n]){
                    match = false;
                    break;
                }
            }
            if(match){
                score++;
            }else{
                match = true;
            }
            
        }
    }
    scores[id] = (score*stringSize[0]) - score - 2;
}
