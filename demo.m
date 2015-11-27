%% Demonstration of box-packing
% David Kline, Zach Renwick, Anqi Sun, Calvin Wang
% 11/(08,09)/15
clear all; close all; clc

profile on
tic
%% Pre-Processing
%P = cubic_grid([0 5; 0 5; 0 5]); % rectangular prism for testing
load('P.mat');
Q = perms([4 4 2])'; % set of orientations
V = find_vertices(P,Q);
if(exist('find_edges_fast')~=3)
    mex find_edges_fast.c;
end

E = find_edges_fast(V);

priority = ones(1,size(E,2));
AD = logical(E);
clear E;
set(0,'RecursionLimit',1500)
x_star = findMIS(AD,priority);

%[A,b] = get_constraints(E);
% 
% %% Solution
% [~,n] = size(A);
% f = -ones(n,1);
% intcon = 1:1:n;
% lb = zeros(n,1);
% ub = ones(n,1);
%x_star = intlinprog(f,intcon,A,b,[],[],lb,ub);
loc = find(x_star==1);
V_star = V(:,loc);

%% Post-Processing
%scatter3(P(1,:),P(2,:),P(3,:))
hold all
show_blocks(V_star)
profile viewer
print(gcf,'-r300','-dpng','demo_sol','-opengl') ;

toc