function vertex_coords = get_vertices(v)
% Rreturns an 3x8 matrix containing the [x;y;z] coords of a
% box v's vertices
% Zach Renwick
% 11/(08,09)/15
    P = v(1:3);
    Q = v(4:6);
    comb_vec = [zeros(1,3);Q'];
    % Produce vectors that point from the origin point P to each of the
    % vertices of the box:
    corner_vecs = allcomb(comb_vec(:,1),comb_vec(:,2),comb_vec(:,3))';
    vertex_coords = P*ones(1,8) + corner_vecs;
end

