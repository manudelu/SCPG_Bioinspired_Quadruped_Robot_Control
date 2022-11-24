clear all
clc

%% train
reps=10; % numero di ripetizioni della sequenza dell'andatura. Ogni sequenza deve essere ripetuta più di una volta durante il processo di learning, altrimenti si ottiene una rete che non è in grado di riprodurre stabilmente l'andatura.
alpha=1.1; % decay factor, deve essere >1 per avere senso fisicamente
Vth=ones(4,1); % tensione di soglia, normalizzata a 1
LearningRate=0.1; % in questo caso, valori bassi di learning rate permettono di ottenere percentuali di convergenza maggiori

% Definizione della sequenza target per ogni andatura; ogni cella avrà 6
% righe (una per gamba) e reps*Tgait(i) colonne (una per ogni istante t)
Scpg_required=cell(1,5);
Scpg_required{1}=logical(repmat([[1;0;0;0],[0;0;0;1],[0;1;0;0],[0;0;1;0]],1,reps));  % Walk
Scpg_required{2}=logical(repmat([[1;0;1;0],[0;1;0;1]],1,reps));  % Trot
Scpg_required{3}=logical(repmat([[1;1;0;0],[0;0;1;1]],1,reps));   % Bound
Scpg_required{4}=logical(repmat([[1;0;0;0],[0;0;1;0],[0;1;0;0],[0;0;0;1]],1,reps))   % Diagonal Walk
Scpg_required{5}=logical(repmat([[1;0;0;0],[0;1;0;0],[0;0;1;0],[0;0;0;1]],1,reps))   % Gallop

Tgait=[4 2 2 4 4]; % istanti che compongono la sequenza base per ogni andatura
% Definizione dei vettori di spike di controllo: il neurone di controllo
% corrispondente spara solo nel primo istante
Sin=cell(1,5); 
Sin{1}=[[1;0;0;0;0],zeros(5,Tgait(1)-1),zeros(5,(reps-1)*Tgait(1))];
Sin{2}=[[0;1;0;0;0],zeros(5,Tgait(2)-1),zeros(5,(reps-1)*Tgait(2))];
Sin{3}=[[0;0;1;0;0],zeros(5,Tgait(3)-1),zeros(5,(reps-1)*Tgait(3))];
Sin{4}=[[0;0;0;1;0],zeros(5,Tgait(4)-1),zeros(5,(reps-1)*Tgait(4))];
Sin{5}=[[0;0;0;0;1],zeros(5,Tgait(5)-1),zeros(5,(reps-1)*Tgait(5))];


n_trials=100;% numero di prove per verificare la convergenza dell'algoritmo
nmax_iterations=10000;% numero massimo di iterazioni
%%

for trial=1:n_trials 
    % inizializzazione randomica dei pesi
    Win=randn(4,5);
    Wcpg=randn(4);
    % pesi correnti
    Win_tmp=Win;
    Wcpg_tmp=Wcpg;
    count=1; % iterazione corrente
    tot_err_current=1; % errore corrente, inizializzato come >0
while tot_err_current>0 && count<=nmax_iterations % continuo il learning finchè l'errore è maggiore di 0 e le iterazioni non superano il numero massimo
    sequence=cell(1,5); % vettore in cui verrà salvata la sequenza di sparo ottenuta dalla rete
    for gait=1:5 % ripeto per ogni andatura
        % iniziallizzo gli spike e la tensione di membrana
        Scpg=zeros(4,1);
        Vcpg=zeros(4,1);
        for t=1:Tgait(gait)*reps % ripeto per ogni istante t
            I=Win*Sin{gait}(:,t)+Wcpg*Scpg; % calcolo la corrente in input per ogni neurone
            Vcpg=Vcpg/alpha+I; % calcolo la tensione di membrana per ogni neurone
            Scpg_prev=Scpg; % salvo gli indici dei neuroni che hanno sparato allo step precedente
            Scpg=Vcpg>Vth; % spike correnti
            Vcpg(Scpg)=0; % azzerro la tensione di membrana dei neuroni che hanno sparato all'istante corrente
            sequence{gait}(:,t)=Scpg;
    
            err=Scpg_required{gait}(:,t)-Scpg; % calcolo errore per l'istante corrente
            % calcolo i termini di aggiornamento delle matrici per l'istante corrente
            deltaWin=err*Sin{gait}(:,t)'.*rand(4,5)*LearningRate;
            deltaWcpg=err*Scpg_prev'.*rand(4,4)*LearningRate;
            % accumulo i termini di aggiornamento ottenuti ad ogni istante
            Win_tmp=Win_tmp+deltaWin;
            Wcpg_tmp=Wcpg_tmp+deltaWcpg;
        end
    end
    % aggiorno i pesi solo dopo aver completato l'iterazione per ogni
    % istante e per ogni andatura
    Win=Win_tmp;
    Wcpg=Wcpg_tmp;
    % errore totale dell'iterazione corrente
    tot_err_current=sum(sum(abs(Scpg_required{1}-sequence{1})))+sum(sum(abs(Scpg_required{2}-sequence{2})))+sum(sum(abs(Scpg_required{3}-sequence{3})))+sum(sum(abs(Scpg_required{4}-sequence{4})))+sum(sum(abs(Scpg_required{5}-sequence{5})));
    tot_err(count)=tot_err_current; % salvo l'errore di tutte le iterazioni per poter eventualmente visualizzare come evolve l'errore
    count=count+1;
end
result(trial)=tot_err_current; % salvo l'errore finale come esito della prova: se è =0 la prova è arrivata a convergenza
Wcpg_def{trial}=Wcpg; 
Win_def{trial}=Win;
end
percent_ok=100*sum(result==0)/n_trials;
% configurazioni della rete che corrispondono a prove arrivate a
% convergenza
Wcpg_ok=Wcpg_def(result==0);
Win_ok=Win_def(result==0);


%% verify
ind=1; % indice della rete di cui si vuole verificare il funzionamento
Wcpg=Wcpg_ok{ind};
Win=Win_ok{ind};

% simulo la rete per il numero di istanti richiesto, per le tre andature e
% salvo la sequenza ottenuta
sequence=cell(1,5);
for gait=1:5
    Vcpg=zeros(4,1);
    Scpg=zeros(4,1);
    for t=1:Tgait(gait)*reps
        I=Win*Sin{gait}(:,t)+Wcpg*Scpg;
        Vcpg=Vcpg/alpha+I;
        Scpg_prev=Scpg;
        Scpg=Vcpg>Vth;
        Vcpg(Scpg)=0;
        sequence{gait}(:,t)=Scpg;
    end
end

% grafico la sequenza ottenuta per verificarne la correttezza (attenzione, bianco e nero sono scambiati rispetto all'articolo. Qui bianco=1, nero=0)
figure

subplot(1,5,1)
imagesc(sequence{1})
colormap('gray')
title('Walk')

subplot(1,5,2)
imagesc(sequence{2})
colormap('gray')
title('Trot')

subplot(1,5,3)
imagesc(sequence{3})
colormap('gray')
title('Bound')

subplot(1,5,4)
imagesc(sequence{4})
colormap('gray')
title('Diagonal Walk')

subplot(1,5,5)
imagesc(sequence{5})
colormap('gray')
title('Gallop')

sgtitle('Quadruped Locomotion')