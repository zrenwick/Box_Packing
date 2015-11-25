function E = find_edges_fast(V)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    E = find_edges_fast_mex(V);
    E = E + E';
end

