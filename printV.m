function printV(V)
   fname = 'v_file.txt';
   fname2 = 'v_data.txt'; 
   fid = fopen(fname,'w');
   fid2 = fopen(fname2,'w');
   [n,m] = size(V);
   fprintf(fid2,'%d,%d',n,m);
   fclose(fid2);
   V = V(:);
   vlen = length(V);
   for k=1:vlen
      fprintf(fid,'%d,',V(k));
   end
   fclose(fid);
end
