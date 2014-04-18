function [kcs,ncs,ccs]=otestspx(datafile,plots);
% otestsp
%   This is an Octave script that find cubic splines for three
%   different boundary conditions: knot-a-not, natural and clamped.
%   (see Preconditions below)
%   When called without left arguments it will print the parameters 
%   of the splines in the screen. 
%
% Usage: otestsp('datafile')        
%        [kcs,ncs,ccs]=otestsp('datafile')        
%        [kcs,ncs,ccs[=otestsp('datafile',plots)
% input arguments
%        datafile = string with complete filename (with extension)
%        plots = integer, 1 generate and save plots
% output arguments
%        kcs - Not-a-knot cubic spline struture
%        ncs - Natural cubic spline struture
%        ccs - Clamped cubic spline struture
%
% Preconditions:
%   * requires (octave-forge) spline toolbox
%   * The data file is a plain text file
%   * The first line of the data file has the derivatives at end-points
%     required for the clamped splines (will be ignored otherwise)
%
% Side effects:
%       Plots  and save the figures of the splines ( if plots=1)
%
% By: Juan C. Cockburn, Nov 25, 2013 (jcck@ieee.org)

%% Check input arguments
if nargin==0
    help otestsp
    return
elseif nargin<2
    plots=0; % default, to not generate files
end

%% Check output arguments
if nargout==0
  verbose=1; % echo on
else
  verbose=0;
end

%% Parse filename and load data (not checking if file exists)
  [pathstr,Data,ext]= fileparts(datafile);
  fname=[Data ext];
  eval(['load -ascii ' fname]);
  eval(['Data=' Data ';']);

%% Extract first line (only used for clampled, otherwise discarded)
  % Clampled boundary conditions;
      yp0 = Data(1,1); % Derivative at first point
	  ypn = Data(1,2); %  Derivative at last point
  % Data Points
       x = Data(2:end,1)'; % Note the transpose operator '
       y = Data(2:end,2)'; % Note the transpose operator '

%% Find splines parameters (construction phase)
   % Clamped cubic spline (also called complete spline) 
       ccs = csape(x,y,'complete',[yp0 ypn]);

   % Natural cubic spline(second derivatives set to zero at endpoints)
       ncs = csape(x,y,'second',[0 0]);

   % Not-a-knot cubic spline
       kcs = csape(x,y,'not-a-knot');

%% Print parameters (stored in field P)
if verbose
     format short
   % not-a-knot spline
     fprintf('Not-a-knot spline parameters d,c,b,a\n')
     disp(kcs.P)
   % natural cspline
     fprintf('Natural spline parameters d,c,b,a\n')
     disp(ncs.P)
   % Clamped spline
     fprintf('Clamped spline parameters d,c,b,a\n')
     disp(ccs.P)
end

%% Draw Plots (only if plots=1)
  if plots
   % clamped case
     figure(1)
     fnplt(kcs); axis equal
     hold on
	 plot(x,ppval(kcs,x),'or'); % plot points
     hold off
     title('Not-a-Knot Cubic Spline')
     xlabel('x');ylabel('y')
     hold off

   % natural case
     figure(2)
     fnplt(ncs); axis equal
     hold on
	 plot(x,ppval(ncs,x),'or'); % plot points
     hold off
     title('Natural Cubic Spline')
     xlabel('x');ylabel('y')

   % not-a-knot case
     figure(3)
     fnplt(ccs); axis equal
     hold on
	 plot(x,ppval(ccs,x),'or'); % plot points
     hold off
     title('Clamped Cubic Spline')
     xlabel('x');ylabel('y')

   % Save figures to files 
     print -f1 -dpng notaknow_splines.png
     print -f2 -dpng natural_splines.png
     print -f3 -dpng clampled_splines.png
  end 

