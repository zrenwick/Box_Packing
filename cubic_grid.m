function P = cubic_grid(lim)
% Creates an array P with P(:,i) being the coordinates of a point in a
% cubic grid (cubes have edge length of 1) with
%   lim = [xmin xmax; ymin ymax; zmin zmax].
% David Kline 11/08/15
  u = lim(1,1):1:lim(1,2);
  v = lim(2,1):1:lim(2,2);
  w = lim(3,1):1:lim(3,2);
  P = [];
  for i = 1:length(u)
    for j = 1:length(v)
      for k = 1:length(w)
        P = [P, [u(i); v(j); w(k)]];
      end
    end
  end
end