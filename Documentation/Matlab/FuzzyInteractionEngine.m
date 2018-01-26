clc

% Read in the data for the FIS
filename = 'FuzzyLogicData.xlsx';
sheetname = 'FuzzyInteractionEngine';
usedrange = 'A3:C32';

testData = xlsread(filename, sheetname, usedrange);
dataSize = size(testData,1);

% Declare a new FIS
mlc_fis = newfis('Fuzzy Interaction Engine');

% Input: Behaviour (Trinary)
mlc_fis = addvar(mlc_fis, 'input', 'Behaviour', [0 90]);
mlc_fis = addmf(mlc_fis, 'input', 1, 'HU', 'trapmf', [0 0 25 35]);              %   Low Honesty
mlc_fis = addmf(mlc_fis, 'input', 1, 'HR', 'trapmf', [25 35 55 65]);            %   Medium Honesty
mlc_fis = addmf(mlc_fis, 'input', 1, 'DhR', 'trapmf',  [55 65 90 90]);          %   High Honesty

% Input: Player Pleasantries
mlc_fis = addvar(mlc_fis, 'input', 'Player Pleasantires', [0 20]);
mlc_fis = addmf(mlc_fis, 'input', 2, 'VL', 'trapmf', [0 0 3 4]);                %   Very Low
mlc_fis = addmf(mlc_fis, 'input', 2, 'L', 'trapmf', [3 4 6 7]);                 %   Low
mlc_fis = addmf(mlc_fis, 'input', 2, 'M', 'trapmf', [6 7 11 12]);               %   Medium
mlc_fis = addmf(mlc_fis, 'input', 2, 'H', 'trapmf', [11 12 14 15]);             %   Heavy
mlc_fis = addmf(mlc_fis, 'input', 2, 'VH', 'trapmf', [14 15 20 20]);            %   Very Heavy

% Input: Current Tile Classification
mlc_fis = addvar(mlc_fis, 'input', 'Tile Classification', [0 10]);
mlc_fis = addmf(mlc_fis, 'input', 3, 'Acceptable', 'trapmf', [0 0 4 6]);        %   Acceptable Tile
mlc_fis = addmf(mlc_fis, 'input', 3, 'Cautious', 'trapmf', [4 6 10 10]);        %   Cautious Tile

% Output: Behaviour Magnitude
mlc_fis = addvar(mlc_fis, 'output', 'Behaviour Magnitude', [0 90]);
mlc_fis = addmf(mlc_fis, 'output', 1, 'Low', 'trapmf', [0 0 25 35]);            %   Low Magnitude
mlc_fis = addmf(mlc_fis, 'output', 1, 'Medium', 'trapmf', [25 35 55 65]);       %   Medium Magnitude
mlc_fis = addmf(mlc_fis, 'output', 1, 'High', 'trapmf', [55 65 90 90]);         %   High Magnitude

% Rulesets
% Constant Honest and Unreliable > Variable Player Pleasantries
rule00 = [1 1 1 3 1 1];
rule01 = [1 2 1 3 1 1];
rule02 = [1 3 1 2 1 1];
rule03 = [1 4 1 2 1 1];
rule04 = [1 5 1 1 1 1];

rule05 = [1 1 2 3 1 1];
rule06 = [1 2 2 2 1 1];
rule07 = [1 3 2 2 1 1];
rule08 = [1 4 2 1 1 1];
rule09 = [1 5 2 1 1 1];

% Constant Honest and Reliable > Variable Player Pleasantries
rule10 = [2 1 1 1 1 1];
rule11 = [2 2 1 2 1 1];
rule12 = [2 3 1 2 1 1];
rule13 = [2 4 1 3 1 1];
rule14 = [2 5 1 3 1 1];

rule15 = [2 1 2 1 1 1];
rule16 = [2 2 2 1 1 1];
rule17 = [2 3 2 1 1 1];
rule18 = [2 4 2 2 1 1];
rule19 = [2 5 2 2 1 1];

% Constant Dishonest and Reliable > Variable Player Pleasantries
rule20 = [3 1 1 1 1 1];
rule21 = [3 2 1 1 1 1];
rule22 = [3 3 1 2 1 1];
rule23 = [3 4 1 2 1 1];
rule24 = [3 5 1 3 1 1];

rule25 = [3 1 2 2 1 1];
rule26 = [3 2 2 2 1 1];
rule27 = [3 3 2 3 1 1];
rule28 = [3 4 2 3 1 1];
rule29 = [3 5 2 3 1 1];

% ruleset containing all the rules
ruleset = [rule00; rule01; rule02; rule03; rule04; rule05; rule06; rule07; rule08; rule09;...
    rule10; rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19;...
    rule20; rule21; rule22; rule23; rule24; rule25; rule26; rule27; rule28; rule29];
    
% ruleset added to the fis
mlc_fis = addrule(mlc_fis, ruleset);
mlc_fis.defuzzMethod = 'bisector';

rules = showrule(mlc_fis)

% this is used to hold the output to be written to excel for testing
actual_magnitude = zeros(dataSize, 1);

% data is read, processed through the fis and then added to the above list
for i=1:size(testData,1)
        eval = evalfis([testData(i, 1), testData(i, 2), testData(i, 3) ], mlc_fis);
        fprintf('%d) In(1): %.2f, In(2) %.2f, In(3) %.2f => Out(1) %.2f Out(2) %.2f \n\n',i,testData(i, 1),testData(i, 2),testData(i, 3), eval);  
        actual_magnitude(i) = eval(1);        
end

% write to the excel file
xlswrite(filename, actual_magnitude, sheetname, ['E3:E' num2str(dataSize+2)]);

% Display the fuzzy inference system sets
figure('Name','Fuzzy Interaction Engine')
% inputs
subplot(3,2,1), plotmf(mlc_fis, 'input', 1)
ylabel('DoM (\mu)');
subplot(3,2,3), plotmf(mlc_fis, 'input', 2)
ylabel('DoM (\mu)');
subplot(3,2,5), plotmf(mlc_fis, 'input', 3)
ylabel('DoM (\mu)');
% output
subplot(3,2,4), plotmf(mlc_fis, 'output', 1)
ylabel('DoM (\mu)');
% a legend holding some additional information
ax = subplot(3, 2, 6);
text(0,0.7,'DoM - Degree of Membership');
text(0,0.5,'Made by Justin Shanks P15225881');
set ( ax, 'visible', 'off')











