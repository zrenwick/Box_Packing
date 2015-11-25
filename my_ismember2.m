function [ found_vec ] = my_ismember2( A, B )
%[ found_vec ] = my_ismember( A, B ) is equivalent to found_vec = ismember(A, B, 'rows')
    len_A = size(A,1);
    len_B = size(B,1);
    B_row_indx_seed = 1:len_B;
    B_row_indx_mat = repmat(B_row_indx_seed,len_A,1);
    B_row_indx = B_row_indx_mat(:);
    % difference matrices must have len_A*len*B rows
    mod_A = repmat(A,len_B,1);
    mod_B = B(B_row_indx,:);
    diff_mat = sum(abs(mod_A-mod_B),2);
    found_indx = find(diff_mat==0);
    row_indx = mod(found_indx-1, len_A)+1;
    found_vec = zeros(len_B,1);
    found_vec(row_indx) = 1;
end

