function E = find_edges(V)
% Constructs an adjacency matrix E from the set of vertices V.
% Calls e = is_edge(v_i,v_j) to determine if two vertices have an edge.
% Zach Renwick
% 11/08/15
    parallel_flag = 0;
    n = size(V,2); % find number of vertices in V
    E = zeros(n,n); % initialize adjacency matrix
    if(~parallel_flag)
        for colnum = 1:n
            col_node = V(:,colnum);
            for rownum = 1:(colnum-1)
                row_node = V(:,rownum);
                % Calculate upper triangular portion of adjacency matrix:
                E(rownum,colnum) = is_edge_fast(row_node,col_node); 
            end
        end
    else
        pool = gcp;
        n_workers = pool.NumWorkers;
        E = ones(n,n);
        E_ut = triu(E,1);
        lin_indx = find(E==E_ut);
        E = zeros(n,n);
        num_indices = length(lin_indx);
        elements_per_worker = ceil(num_indices/n_workers);
        worker_indices = cell(1,n_workers);
        for k = 0:(n_workers-1)
            start_indx = k*elements_per_worker + 1;
            end_indx = (k+1)*elements_per_worker;
            if(end_indx > length(lin_indx))
                end_indx = length(lin_indx);
            end
            worker_indices{k+1} = lin_indx(start_indx:end_indx);
        end
        work_arrays = cell(1,n_workers);
        parfor work_num = 1:n_workers
            lin_indx = worker_indices{work_num};
            num_points = length(lin_indx);
            work_array = zeros(1,num_points);
            a = 1;
            b = 1;
            c = a-b;
            for k = 1:num_points;
                [rownum, colnum] = ind2sub([n,n],lin_indx(k));
                col_node = V(:,colnum);
                row_node = V(:,rownum);
                % Calculate upper triangular portion of adjacency matrix:
                work_array(k) = is_edge(row_node,col_node); 
            end
            work_arrays{work_num} = work_array;
        end
        for work_num = 1:n_workers
            lin_indx = worker_indices{work_num};
            array = work_arrays{work_num};
            E(lin_indx) = array;
        end
        
    end
    % Add upper triangular portion to its transpose to get symmetric 
    % adjacency matrix:
    E = E + E';  
end