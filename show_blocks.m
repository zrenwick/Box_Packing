function show_blocks( V_set, varargin )
% Takes a set of block locations v = [P;Q] and plots them with
% alternating colors
% Zach Renwick
% 11/(08,09)/15
    if(length(varargin)>0)
        colors = varargin{1};
    else
        colors = 'rgbcmyk';
    end
    alph_val = 0.5;
    n_colors = length(colors);
    color_indx = 0;
    for v_indx = 1:size(V_set,2)
        v = V_set(:,v_indx);
        color_indx = mod(color_indx, n_colors)+1;
        color = colors(color_indx);
        vertices = get_vertices(v);
        hold on
        for k = 1:3
            ordered_vertices = sortrows(vertices',k)';
            square1verts = ordered_vertices(:,[1,2,4,3]);
            square2verts = ordered_vertices(:,[1,2,4,3]+4);
            sqr1 = fill3(square1verts(1,:),square1verts(2,:),...
                         square1verts(3,:),color);
            sqr2 = fill3(square2verts(1,:),square2verts(2,:),...
                         square2verts(3,:),color);
            alpha(sqr1,alph_val);
            alpha(sqr2,alph_val);
        end
    end
    xlabel('X')
    ylabel('Y')
    zlabel('Z')
    axis equal
end

