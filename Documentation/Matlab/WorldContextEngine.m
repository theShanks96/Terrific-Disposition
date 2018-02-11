clc

% Read in the data for the FIS
filename = 'FuzzyLogicData.xlsx';
sheetname = 'WorldContextEngine';
usedrange = 'A3:C47';

testData = xlsread(filename, sheetname, usedrange);
dataSize = size(testData,1);

% Declare a new FIS
mlc_fis = newfis('World Context Engine');

% Input: Honesty Index (%)
mlc_fis = addvar(mlc_fis, 'input', 'Honesty Index', [0 100]);
mlc_fis = addmf(mlc_fis, 'input', 1, 'L', 'trapmf', [0 0 30 40]);               %   Low Honesty
mlc_fis = addmf(mlc_fis, 'input', 1, 'M', 'trapmf', [30 40 60 70]);             %   Medium Honesty
mlc_fis = addmf(mlc_fis, 'input', 1, 'H', 'trapmf',  [60 70 100 100]);          %   High Honesty

% Input: Playstyle
mlc_fis = addvar(mlc_fis, 'input', 'Playstyle', [0 100]);                    
mlc_fis = addmf(mlc_fis, 'input', 2, 'Slow', 'trapmf', [0 0 20 30]);          %   Slow
mlc_fis = addmf(mlc_fis, 'input', 2, 'Medium', 'trapmf', [20 30 60 70]);  %   Medium
mlc_fis = addmf(mlc_fis, 'input', 2, 'Fast', 'trapmf', [60 70 100 100]);        %   Fast

% Input: Player Hostility
mlc_fis = addvar(mlc_fis, 'input', 'Player Hostility', [0 100]);
mlc_fis = addmf(mlc_fis, 'input', 3, 'VL', 'trapmf', [0 0 15 20]);              %   Very Low
mlc_fis = addmf(mlc_fis, 'input', 3, 'L', 'trapmf', [15 20 30 35]);             %   Low
mlc_fis = addmf(mlc_fis, 'input', 3, 'M', 'trapmf', [30 35 55 60]);           %   Medium
mlc_fis = addmf(mlc_fis, 'input', 3, 'H', 'trapmf', [55 60 70 75]);         %   Heavy
mlc_fis = addmf(mlc_fis, 'input', 3, 'VH', 'trapmf', [70 75 100 100]);        %   Very Heavy

% Output: Behaviour
mlc_fis = addvar(mlc_fis, 'output', 'Behaviour', [0 90]);
mlc_fis = addmf(mlc_fis, 'output', 1, 'HU', 'trapmf', [0 0 25 35]);             %   Honest and Unreliable
mlc_fis = addmf(mlc_fis, 'output', 1, 'HR', 'trapmf', [25 35 55 65]);           %   Honest and Reliable
mlc_fis = addmf(mlc_fis, 'output', 1, 'DhR', 'trapmf', [55 65 90 90]);        %   Dishonest and Reliable

% Rulesets
% Constant Low Honesty > Variable Playstyle and Player Aggression
rule00 = [1 1 1 2 1 1];
rule01 = [1 1 2 2 1 1];
rule02 = [1 1 3 1 1 1];
rule03 = [1 1 4 1 1 1];
rule04 = [1 1 5 3 1 1];

rule05 = [1 2 1 2 1 1];
rule06 = [1 2 2 2 1 1];
rule07 = [1 2 3 1 1 1];
rule08 = [1 2 4 1 1 1];
rule09 = [1 2 5 3 1 1];

rule10 = [1 3 1 2 1 1];
rule11 = [1 3 2 2 1 1];
rule12 = [1 3 3 1 1 1];
rule13 = [1 3 4 1 1 1];
rule14 = [1 3 5 3 1 1];

% Constant Medium Honesty > Variable Playstyle and Player Aggression
rule15 = [2 1 1 2 1 1];
rule16 = [2 1 2 1 1 1];
rule17 = [2 1 3 1 1 1];
rule18 = [2 1 4 1 1 1];
rule19 = [2 1 5 3 1 1];

rule20 = [2 2 1 2 1 1];
rule21 = [2 2 2 1 1 1];
rule22 = [2 2 3 1 1 1];
rule23 = [2 2 4 3 1 1];
rule24 = [2 2 5 3 1 1];

rule25 = [2 3 1 2 1 1];
rule26 = [2 3 2 1 1 1];
rule27 = [2 3 3 1 1 1];
rule28 = [2 3 4 3 1 1];
rule29 = [2 3 5 3 1 1];

% Constant High Honesty > Variable Playstyle and Player Aggression
rule30 = [3 1 1 2 1 1];
rule31 = [3 1 2 2 1 1];
rule32 = [3 1 3 1 1 1];
rule33 = [3 1 4 1 1 1];
rule34 = [3 1 5 3 1 1];

rule35 = [3 2 1 2 1 1];
rule36 = [3 2 2 2 1 1];
rule37 = [3 2 3 1 1 1];
rule38 = [3 2 4 1 1 1];
rule39 = [3 2 5 3 1 1];

rule40 = [3 3 1 2 1 1];
rule41 = [3 3 2 2 1 1];
rule42 = [3 3 3 1 1 1];
rule43 = [3 3 4 1 1 1];
rule44 = [3 3 5 3 1 1];

% ruleset containing all the rules
ruleset = [rule00; rule01; rule02; rule03; rule04; rule05; rule06; rule07; rule08; rule09;...
    rule10; rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19;...
    rule20; rule21; rule22; rule23; rule24; rule25; rule26; rule27; rule28; rule29;...
    rule30; rule31; rule32; rule33; rule34; rule35; rule36; rule37; rule38; rule39;...
    rule40; rule41; rule42; rule43; rule44];
    
% ruleset added to the fis
mlc_fis = addrule(mlc_fis, ruleset);
mlc_fis.defuzzMethod = 'bisector';

rules = showrule(mlc_fis)

% this is used to hold the output to be written to excel for testing
actual_behaviour = zeros(dataSize, 1);

% data is read, processed through the fis and then added to the above list
for i=1:size(testData,1)
        eval = evalfis([testData(i, 1), testData(i, 2), testData(i, 3) ], mlc_fis);
        fprintf('%d) In(1): %.2f, In(2) %.2f, In(3) %.2f => Out(1) %.2f Out(2) %.2f \n\n',i,testData(i, 1),testData(i, 2),testData(i, 3), eval);  
        actual_behaviour(i) = eval(1);
end

% write to the excel file
xlswrite(filename, actual_behaviour, sheetname, ['E3:E' num2str(dataSize+2)]);

% Display the fuzzy inference system sets
figure('Name','World Context Engine')
% inputs
subplot(3,2,1), plotmf(mlc_fis, 'input', 1)
ylabel('DoM (\mu)');
subplot(3,2,3), plotmf(mlc_fis, 'input', 2)
ylabel('DoM (\mu)');
subplot(3,2,5), plotmf(mlc_fis, 'input', 3)
ylabel('DoM (\mu)');
% outputs
subplot(3,2,4), plotmf(mlc_fis, 'output', 1)
ylabel('DoM (\mu)');
% a legend holding some additional information
ax = subplot(3, 2, 6);
text(0,0.7,'DoM - Degree of Membership');
text(0,0.5,'Made by Justin Shanks P15225881');
set ( ax, 'visible', 'off')











