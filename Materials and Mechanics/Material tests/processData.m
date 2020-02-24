%% Load parameters

allParameters = readmatrix(uigetfile('*.xlsx'));
%%
[filename, filepath] = uigetfile('*.csv');
for i = 1:12
    process(allParameters,i, filename, filepath)
end
%%
function process(allParameters, i, filename, filepath)
    for j=1:2
        %Match pattern to dynamically read the files
        filename = regexprep(filename, '_\d+\d?+_+\d', ['_',num2str(i),'_',num2str(j)]);
        T = readmatrix([filepath filename]);
        %time = T(:,1);
        displacement = T(:,2);
        force=T(:,3);
        plotTitle=['Sample ' num2str(i)];
        
        %% Process Data
        % set parameters for the particular graph we're working on.
        parameters=allParameters(allParameters(:,3)==i,:);
        %Take dimensions from our set of parameters
        A=parameters(6)*parameters(8)*1e-6; %Width * length in m^2
        L = parameters(8)*1e-3;
        stress=force/A;
        strain=displacement/L;
        %youngModulus=stress./strain;
        figure,plot(strain,stress);
        xlabel('Strain'); ylabel('Stress, N/m^2')
        title(plotTitle);
    end
end