function [ output ] = my_ismember( A, B, varargin)
    if(~isempty(varargin))
        anyall = varargin{1};
        if(strcmp(anyall,'any'))
            any_flag = 1;
            all_flag = 0;
            output = 0; %if we don't find any matches, then any = 0
        elseif(strcmp(anyall,'all'))
            any_flag = 0;
            all_flag = 1;
            output = 1; %if we don't find any non-matches, then all = 1
        else
            error('The third argument to "my_ismember" must be a string containing "any" or "all"')
        end
    else
        any_flag = 0;
        all_flag = 0;
    end
        
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
    
    if(~(any_flag||all_flag))
        output = zeros(len_B,1);
    end

    for b_row_num = 1:len_B
        B_row = B(b_row_num, :);
        b_test_mat = repmat(B_row,len_A,1);
        diff_mat = sum(abs(A-b_test_mat),2);
        
        if(any(~diff_mat)) % we go here if this column of B matches a column in A
            if(any_flag) % If in "any" mode, we can return 1 now since at least one element matches
                output = 1; 
                return
            elseif(all_flag)
                continue
            else
                output(b_row_num) = 1;
            end
        else % we go here if this column of B does not match any columns in A
            if(all_flag) % If in "all" mode, we can return 0 now since at least one element doesn't match
                output = 0;
                return
            elseif(any_flag)
                continue
            else
                output(b_row_num) = 0;
            end
        end
    end
end

