function E = find_edges_fast(V)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    if(exist('find_edges_fast_mex','file')~=3)
        mex find_edges_fast_mex.c   %compile mex if it already hasn't been
    end

    E = find_edges_fast_mex(V);
    E = E + E';
end

