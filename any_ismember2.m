function [ output ] = any_ismember2( A, B)
%UNTITLED5 Summary of this function goes here
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
    output = 0; % if we don't find a match, we default to there being no matches, so any = false;
    for b_row_num = 1:len_B
        B_row = B(b_row_num, :);
        b_test_mat = repmat(B_row,len_A,1);
        diff_mat = sum(abs(A-b_test_mat),2);
        
        if(any(~diff_mat)) % we go here if this column of B matches a column in A            
            output = 1; 
            return
        end
    end
end

