function [ output ] = all_ismember( A, B)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
    len_A = size(A,1);
    len_B = size(B,1);
    if(len_A < len_B)
        A_temp = A;
        A = B;
        B = A_temp;
        len_A_temp = len_A;
        len_A = len_B;
        len_B = len_A_temp;
    end
    output = 1; % if we don't find any non-matches, then we default to all members matching
    for b_row_num = 1:len_B
        B_row = B(b_row_num, :);
        b_test_mat = repmat(B_row,len_A,1);
        diff_mat = sum(abs(A-b_test_mat),2); 
        if(~any(~diff_mat)) % we go here if this column of B does not match any columns in A
            output = 0;
            return
        end
    end
end

