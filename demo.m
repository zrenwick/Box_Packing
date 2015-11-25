%% Demonstration of box-packing
% David Kline, Zach Renwick, Anqi Sun, Calvin Wang
% 11/(08,09)/15
clear all; close all; clc

if(exist('is_edge_fast','file')~=3)
    mex is_edge_fast.c   %compile mex if it already hasn't been
end
profile on
tic
%% Pre-Processing
P = cubic_grid([0 15; 0 10; 0 10]); % rectangular prism for testing
% load('P.mat');
 Q = perms([4 2 1])'; % set of orientations
 V = find_vertices(P,Q);
 E = find_edges_fast(V);
% keyboard
%load('E.mat');
priority = ones(1,size(E,2));
x_star = findMIS(logical(E),priority);

%E2 = find_edges(V);

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
scatter3(P(1,:),P(2,:),P(3,:))
hold all
show_blocks(V_star)
profile viewer
print(gcf,'-r300','-dpng','demo_sol','-opengl') ;

toc