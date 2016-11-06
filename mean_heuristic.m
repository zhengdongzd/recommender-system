diary('experiments\mean_ihou_output_heuristic.txt');

diary on;

song=load('D:\\LiuQi\\DZ\\Ï¡ÊèMaxMat\\data\\ihou130.txt');

A=load('D:\\LiuQi\\DZ\\Ï¡ÊèMaxMat\\data\\ihouMatrixR.txt');
i=A(:,1);
j=A(:,2);
s=A(:,3);
R=sparse(i,j,s);
out = [0,0,0,0,0];

sum_coverage = 0;
sum_targets = 0;
sum_covered_percentage = 0;
count=0;

for target=5:10:130
    count=count+1;
    seedNum=3*target;
    r = song(1:target,:);
    T=r;
    heuristic(R,seedNum,r);
    S=dlmread('greedyheuristic.txt',',');
    
    
    
    
    %ConstraintedInfluenceCoverage(R,S,T);
    [M,N]=size(R);   %M #rows, N #columns
    p=false(M,1);    %none are covered
    s=size(S)
    t=size(T)
    pt=false(t(2),1);
    
    for c=1:s(2)
        for col=1:M
            if R(col,S(c))>0, p(col)=true; end
        end
        for colt=1:t(2)
            if R(T(colt),S(c))>0,pt(colt)=true; end 
        end
    end
    
    coverage=0;
    for c=1:M
        if p(c), coverage=coverage+1; end
    end
    %fprintf('coverage=%d\n',coverage);
    
    
    targetcoverage=0;
    for c=1:t(2)
        if pt(c), targetcoverage=targetcoverage+1; end
    end
    
    %fprintf('targets=%d,\t Covered Percentage=%d\n',t(2),targetcoverage/t(2));
    
    coverage
    t(2)
    targetcoverage/t(2)
 	
    out = [out;[t(1),s(2),coverage,t(2),targetcoverage/t(2)]];
    
    sum_coverage = sum_coverage + coverage;
    sum_targets = sum_targets + t(2);
    sum_covered_percentage = sum_covered_percentage + targetcoverage/t(2);

end

sum_coverage/count
sum_targets/count
sum_covered_percentage/count

out=[out;[0,0,sum_coverage/count,sum_targets/count,sum_covered_percentage/count]];

diary off;
xlswrite('heuristic.xls', out)
