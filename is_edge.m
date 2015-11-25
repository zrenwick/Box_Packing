function e = is_edge(v1,v2)
% Determines if the boxes associated with vertices v1, v2 overlap.
% Computes point at center of each unit cube of box and checks if the two
% boxes share any of these points.
% Anqi Sun
% 11/08/15
	p1 = v1(1:3);
    q1 = v1(4:6);
    p2 = v2(1:3);
    q2 = v2(4:6);
    vert1 = zeros(8,3);
    vert2 = zeros(8,3);
    s = 1;
    e = 0;
    for i = 0:(q1(1)-1)
        for j = 0:(q1(2)-1)
            for k = 0:(q1(3)-1)
                vert1(s,1) = p1(1)+0.5+i;
                vert1(s,2) = p1(2)+0.5+j;
                vert1(s,3) = p1(3)+0.5+k;
                s = s+1;
            end
        end
    end
    s = 1;
    for i = 0:(q2(1)-1)
        for j = 0:(q2(2)-1)
            for k = 0:(q2(3)-1)
                vert2(s,1) = p2(1)+0.5+i;
                vert2(s,2) = p2(2)+0.5+j;
                vert2(s,3) = p2(3)+0.5+k;
                s = s+1;
            end
        end
    end
    e = any(ismember(vert1,vert2,'rows'));
end
