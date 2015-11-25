function [A, b] = get_constraints(E)
% Computes A, b for constraint Ax <= b from adjacency matrix E.
% This is the constraint that optimal solution has no edges.
% Calvin Wang
% Zach Renwick updated 11/15 to improve speed
% 11/08/15
    n_variables = size(E,1);
    n_constraints = sum(sum(E))/2;
%     A = zeros(n_constraints, n_variables);
%     constr_num = 0;
%     for i = 1:n_variables
%         for j = 1:i
%             if E(i,j) == 1
%                 constr_num = constr_num + 1;
%                 A(constr_num,i) = 1;
%                 A(constr_num,j) = 1;
%                 a = zeros(1, size(E,1));
%                 a(i) = 1;
%                 a(j) = 1;
%                 A = [A;a];
%             end
%         end
%     end    
    
    A = zeros(n_constraints, n_variables);       % pre-allocate memory for constraint matrix
    size_A = [n_constraints, n_variables];       % store the size of the A matrix in an array for use in index conversions
    E_ut = triu(E);                              % get only upper triangular portion of adjacency matrix
    [I,J] = find(E_ut==1);                       % Find the indices (i,j) of all edges in the adjacency matrix
    constr_num = 1:n_constraints;                % Create an array containing the row indices of the A matrix
    lin_indx1 = sub2ind(size_A,constr_num, I');% Convert the indices of the "1" elements of the constraint matrix into linear indices
    lin_indx2 = sub2ind(size_A,constr_num, J');% Convert the indices of the "1" elements of the constraint matrix into linear indices
    A([lin_indx1,lin_indx2]) = 1;               % Set the non-zero elements of the A matrix using the linear indices we just created
    b = ones(n_constraints,1);
end