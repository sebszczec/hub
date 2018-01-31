pipeline {
    agent any 

    stages {
        stage('Build docker image') { 
            steps { 
                sh 'docker build -t ci_hub .' 
            }
        }
        stage('Run UT'){
            steps {
                sh 'docker run -P -v "${WORKSPACE}" ci_hub /bin/bash -c "cmake . && make && ./ut"' 
            }
        }
    }
}
