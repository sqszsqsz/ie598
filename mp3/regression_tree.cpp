
#include <RInside.h>                    // for the embedded R via RInside
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {

    // create an embedded R instance
    RInside R(argc, argv);               

    std::string cmd = "library(DMwR);"
        "library(rpart);"
        "algae <- algae[-manyNAs(algae),];"
        "rt.a1 <- rpart(a1 ~ ., data = algae[,1:12]);"
        "rt.a1;"
        "rt.a1_autoprune <- prune(tree = rt.a1, cp = rt.a1$cptable[which.min(rt.a1$cptable[,'xerror']+rt.a1$cptable[,'xstd']),'CP']);"
        "prettyTree(rt.a1_autoprune);"
        "tmpf <- tempfile('regression_tree', fileext='.png'); "  
        "png(tmpf); "
        "print(prettyTree(rt.a1_autoprune)); "
        "dev.off();"
        "tmpf";

    // by running parseEval, we get the last assignment back, here the filename
    std::string tmpfile = R.parseEval(cmd);
    std::cout << "Can now use plot in " << tmpfile << std::endl;
    std::string plot_command = ("open ");
    plot_command += tmpfile;
    //std::cout << plot_command << std::endl;
    system(plot_command.c_str());
    
    exit(0);
}

