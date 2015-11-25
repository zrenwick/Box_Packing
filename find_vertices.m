function V = find_vertices(P,Q)
% Finds vertices of the graph (i.e., valid box placements)
% Calvin Wang & David Kline 
% 11/09/15
  V = [];
  for i = 1:length(P)
    for j = 1:length(Q)
      p = P(:,i);
      q = Q(:,j);
      A = cubic_grid([p p+q]);
      if(all_ismember(A',P'))
        V = [V, [p;q]];
      end
    end
  end
end