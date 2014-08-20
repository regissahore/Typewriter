function setting = get_setting()
    setting = {};
    setting.debug = true;
    setting.train.image = 'train_image/';
    setting.train.annotation = 'train_annotation/';
    setting.train.bing = 'train_bing/';
    setting.test.image = 'test_image/';
    setting.test.result = 'test_result/';
    setting.test.annotation = 'test_annotation/';
    setting.test.bing = 'test_bing/';
    setting.evaluate = 'evaluate_result/';
    setting.Nw = 1;
    setting.Ng = 4;
    setting.sizes = [10, 20, 40, 80, 160];
    setting.proposal_num = 10000;
    
    setting.positive_file = 'positve.mat';
    setting.negative_file = 'negative.mat';
    setting.model_w_file = 'model_w.mat';
    setting.model_a_file = 'model_a.mat';
    setting.model_o_file = 'model_o.mat';
    setting.result_dr_file = 'result_dr.mat';
end